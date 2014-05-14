#pragma once
#ifndef INCLUDE_GUARD_cppcomponents_curl_HTTP_CLIENT_HPP_10_21_2013_
#define INCLUDE_GUARD_cppcomponents_curl_HTTP_CLIENT_HPP_10_21_2013_


#include "cppcomponents_curl.hpp"
#include <fstream>
#include <cppcomponents_asio_runtime/cppcomponents_asio_runtime.hpp>

namespace cppcomponents_curl{


	struct Request{

		std::string Url;
		std::string Method;
		std::vector<std::pair<std::string, std::string>> Headers;
		std::string Body;
		std::string Username;
		std::string Password;
		std::int32_t AuthMode = 0;
		std::int32_t ConnectTimeout = 0;
		std::int32_t RequestTimeout = 0;

		bool FollowRedirects = true;;
		int MaxRedirects = -1;
		std::string UserAgent;
		bool UseGzip = true;
		std::string NetworkInterface;
		std::string ProxyHost;
		int ProxyPort = 0;
		std::string ProxyUsername;
		std::string ProxyPassword;
		bool AllowNonStandardMethods = false;
		bool ValidateCert = true;
		std::string CACerts;
		bool AllowIPv6 = true;
		std::string ClientKey;
		std::string ClientCert;
		std::string Referer;
		std::string Cookie;
		std::string CookieFile;

		std::string DownloadFileName;


		cppcomponents::Channel<cppcomponents::use<cppcomponents::IBuffer>> StreamingChannel;
		cppcomponents::Channel<cppcomponents::use<cppcomponents::IBuffer>> HeaderChannel;
		cppcomponents::Channel<std::tuple<double, double, double, double>> ProgressChannel;



		Request(){ Initialize(); }
		Request(const std::string& url) :Url{ url }{ Initialize(); }
		Request(const char* url) :Url{ url }{ Initialize(); }

	private:
		void Initialize(){
			CACerts = "cacert.pem";
		}
	};
	struct CurlClient{
	private:

		cppcomponents::use<IMulti> multi_;
		Easy easy_;
	
		Response response_;
		cppcomponents::Future<void> done_saving_to_file_;
		cppcomponents::Channel<cppcomponents::use<cppcomponents::IBuffer>> chan_;

		struct EasyAborter{
			cppcomponents::use<IEasy> easy_;

			EasyAborter(cppcomponents::use<IEasy> easy) :easy_{ easy }{}
			void Commit(){ easy_ = nullptr; }
			
			~EasyAborter(){
				try{
					if (!easy_)return;
					auto multi = Curl::DefaultMulti();
					multi.Remove(easy_, Constants::Errors::CURLE_ABORTED_BY_CALLBACK);
				}
				catch (...){}
			}

		};

		static void HandleStreamingDownload(cppcomponents::use<IEasy> easy, cppcomponents::Future<void> done, std::shared_ptr<std::ofstream> pof, cppcomponents::Channel<cppcomponents::use<cppcomponents::IBuffer>> chan,
			cppcomponents::Future<cppcomponents::use<cppcomponents::IBuffer>> f){
			EasyAborter aborter{ easy };
			using namespace cppcomponents::asio_runtime;
			auto blocking = Runtime::GetBlockingThreadPool();
			if (f.ErrorCode() == cppcomponents::error_abort::ec){
				cppcomponents::async(blocking, [pof, done](){
					pof->flush();
					pof->close();
					done.QueryInterface<cppcomponents::IPromise<void>>().Set();
				});
				aborter.Commit();
			}
			else{
				auto buf = f.Get();
				cppcomponents::async(blocking, [pof, chan, buf, easy,done]()mutable{
					EasyAborter aborter{ easy };
					pof->write(buf.Begin(), buf.Size());
					chan.Read().Then(Runtime::GetThreadPool(), std::bind(HandleStreamingDownload, easy, done,pof, chan, std::placeholders::_1));
					aborter.Commit();
				});
			}
			aborter.Commit();

		}

		 void OpenFileAndHandleStreamingDownload(cppcomponents::use<IEasy> easy,  std::string filename, cppcomponents::Channel<cppcomponents::use<cppcomponents::IBuffer>> chan,
			cppcomponents::Future<cppcomponents::use<cppcomponents::IBuffer>> f){
			EasyAborter aborter{ easy };
			using namespace cppcomponents;
			using namespace cppcomponents::asio_runtime;
			if (f.ErrorCode() == cppcomponents::error_abort::ec){
				done_saving_to_file_.QueryInterface<cppcomponents::IPromise<void>>().Set();
				aborter.Commit();
				return;
			}
			auto buf = f.Get();
			std::shared_ptr<std::ofstream> pof = std::make_shared<std::ofstream>(filename);
			if (!*pof){
				done_saving_to_file_.QueryInterface<cppcomponents::IPromise<void>>().SetError(cppcomponents::error_invalid_arg::ec);
				throw cppcomponents::error_invalid_arg();
			}
			pof->write(buf.Begin(), buf.Size());
			chan.Read().Then(Runtime::GetThreadPool(), std::bind(HandleStreamingDownload, easy, done_saving_to_file_, pof, chan, std::placeholders::_1));
			aborter.Commit();


		}

		void HandleOptions(const Request& req){
			easy_.SetPointerOption(Constants::Options::CURLOPT_URL, const_cast<char*>(req.Url.c_str()));

			HandleMethod(req);
			HandleWriteFunction(req);
			HandleHeaderFunction(req);
			HandleProgressFunction(req);


			// Handle headers
			if (!req.Headers.empty()){
				Slist sl;
				for (auto& p : req.Headers){
					sl.Append(p.first + ':' + p.second);
				}
				easy_.SetPointerOption(Constants::Options::CURLOPT_HEADER, sl.get_portable_base());
			}

			// Rest of options handled alphabetically
			//#define CURL_IPRESOLVE_WHATEVER 0 default, resolves addresses to all IP
			//			versions that your system allows 
			//#define CURL_IPRESOLVE_V4       1 /* resolve to ipv4 addresses 
			//#define CURL_IPRESOLVE_V6       2 /* resolve to ipv6 addresses 
			if (req.AllowIPv6){
				easy_.SetInt32Option(Constants::Options::CURLOPT_IPRESOLVE, 1);
			}
			else{
				easy_.SetInt32Option(Constants::Options::CURLOPT_IPRESOLVE, 0);
			}

			easy_.SetInt32Option(Constants::Options::CURLOPT_HTTPAUTH, req.AuthMode);

			if (req.CACerts.size()){
				easy_.SetStringOption(Constants::Options::CURLOPT_CAINFO, req.CACerts);
			}

			if (req.ClientCert.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_SSLCERT, req.ClientCert);
			}
            if (req.ClientKey.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_KEYPASSWD, req.ClientKey);

            }
            if (req.ConnectTimeout != 0){
                easy_.SetInt32Option(Constants::Options::CURLOPT_CONNECTTIMEOUT_MS, req.ConnectTimeout);
            }
            if (req.Cookie.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_COOKIE, req.Cookie);
            }
            if (req.CookieFile.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_COOKIEFILE, req.CookieFile);
            }
            
            easy_.SetInt32Option(Constants::Options::CURLOPT_FOLLOWLOCATION, req.FollowRedirects ? 1 : 0);

            if (req.MaxRedirects != 0){
                easy_.SetInt32Option(Constants::Options::CURLOPT_MAXREDIRS, req.MaxRedirects);
            }

            if (req.NetworkInterface.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_INTERFACE, req.NetworkInterface);
            }

            if (req.Password.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_PASSWORD, req.Password);
            }

            if (req.ProxyHost.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_PROXY, req.ProxyHost);
            }

            if (req.ProxyPort != 0){
                easy_.SetInt32Option(Constants::Options::CURLOPT_PROXYPORT, req.ProxyPort);
            }

            if (req.ProxyPassword.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_PROXYPASSWORD, req.ProxyPassword);
            }
            if (req.ProxyUsername.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_PROXYUSERNAME, req.ProxyUsername);
            }
            if (req.Referer.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_REFERER, req.Referer);
            }

            if (req.RequestTimeout != 0){
                easy_.SetInt32Option(Constants::Options::CURLOPT_TIMEOUT_MS, req.RequestTimeout);
            }

            if (req.Url.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_URL, req.Url);
            }
            if (req.UseGzip){
                easy_.SetStringOption(Constants::Options::CURLOPT_ACCEPT_ENCODING, "");
            }
            if (req.UserAgent.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_USERAGENT, req.UserAgent);
            }
            if (req.Username.size()){
                easy_.SetStringOption(Constants::Options::CURLOPT_USERNAME, req.Username);
            }
            
            easy_.SetInt32Option(Constants::Options::CURLOPT_SSL_VERIFYHOST, req.ValidateCert ? 2 : 0);

            HandleMethod(req);
            HandleWriteFunction(req);
            HandleProgressFunction(req);
            HandleHeaderFunction(req);

		}

		void HandleMethod(const Request& req){
			// Default to GET
			if (req.Method.size() == 0 || req.Method == "GET"){
				easy_.SetInt32Option(Constants::Options::CURLOPT_HTTPGET, 1);

			}
			else if (req.Method == "PUT"){
				auto body = req.Body;
				easy_.SetInt32Option(Constants::Options::CURLOPT_UPLOAD, 1);
				easy_.SetInt32Option(Constants::Options::CURLOPT_INFILESIZE, body.size());
				std::size_t pos = 0;
				easy_.SetFunctionOption(Constants::Options::CURLOPT_READFUNCTION,
					cppcomponents::make_delegate<Callbacks::ReadFunction>([body, pos](void* ptr, std::size_t size,
					std::size_t nmemb)mutable -> std::size_t{
					if (pos >= body.size()){
						return 0;
					}
					auto cptr = static_cast<char*>(ptr);
					auto count = size*nmemb;
					auto remaining = body.size() - pos;
					auto begin = &body[0];
					auto end = begin + body.size();;
					if (remaining <= count){
						std::copy(begin + pos, end, cptr);
						pos = body.size();
						return remaining;
					}
					else{
						std::copy(begin + pos, begin + pos + count, cptr);
						pos += count;
						return count;
					}

				}));
			}

			else if (req.Method == "POST"){
				auto body = req.Body;
				easy_.SetInt32Option(Constants::Options::CURLOPT_POST, 1);
				easy_.SetInt32Option(Constants::Options::CURLOPT_POSTFIELDSIZE, body.size());
				char* begin = 0;
				if (body.size()){
					begin = const_cast<char*>(&body[0]);
				}
				easy_.SetPointerOption(Constants::Options::CURLOPT_COPYPOSTFIELDS, begin);


			}
			else if (req.Method == "DELETE"){
				easy_.SetPointerOption(Constants::Options::CURLOPT_CUSTOMREQUEST, const_cast<char*>("DELETE"));


			}
			else if (req.Method == "HEAD"){
				easy_.SetInt32Option(Constants::Options::CURLOPT_HTTPGET, 1);
				easy_.SetInt32Option(Constants::Options::CURLOPT_NOBODY, 1);


			}
			else if (req.AllowNonStandardMethods){
				easy_.SetStringOption(Constants::Options::CURLOPT_CUSTOMREQUEST, req.Method);
			}
			else{
				throw cppcomponents::error_invalid_arg();
			}
		}

		static void CleanupCallbacks(cppcomponents::use<IEasy> easy){
			easy.SetFunctionOption(Constants::Options::CURLOPT_WRITEFUNCTION, nullptr);
			easy.SetFunctionOption(Constants::Options::CURLOPT_READFUNCTION, nullptr);
			easy.SetFunctionOption(Constants::Options::CURLOPT_HEADERFUNCTION, nullptr);
			easy.SetFunctionOption(Constants::Options::CURLOPT_PROGRESSFUNCTION, nullptr);
		}

		void HandleWriteFunction(const Request& req){
			cppcomponents::use<Callbacks::WriteFunction> writer_func;
			if (req.StreamingChannel || req.DownloadFileName.size()){
				auto chan = req.StreamingChannel;
				if (req.DownloadFileName.size()){
					if (!chan){
						chan = cppcomponents::make_channel<cppcomponents::use<cppcomponents::IBuffer>>();
					}
					chan_ = chan;
					done_saving_to_file_ = cppcomponents::make_promise<void>().QueryInterface<cppcomponents::IFuture<void>>();
					chan.Read().Then(cppcomponents::asio_runtime::Runtime::GetBlockingThreadPool(), std::bind(&CurlClient::OpenFileAndHandleStreamingDownload,this, easy_, req.DownloadFileName, chan, std::placeholders::_1));
				}				
				
				auto func = [chan](char* p, std::size_t n, std::size_t nmemb) mutable -> std::size_t{
					auto sz = n*nmemb;
					auto buffer = cppcomponents::Buffer::Create(sz);
					buffer.SetSize(sz);
					std::copy(p, p + sz, buffer.Begin());
					chan.Write(buffer);
					return sz;
				};

				writer_func = cppcomponents::make_delegate<Callbacks::WriteFunction>(func);

			}
			else{
				auto response_writer = response_.as<IResponseWriter>();
				auto func = [response_writer](char* p, std::size_t n, std::size_t nmemb) mutable -> std::size_t{
					auto sz = n*nmemb;
					response_writer.AddToBody(p, p + sz);
					return sz;
				};
				writer_func = cppcomponents::make_delegate<Callbacks::WriteFunction>(func);
			}

			easy_.SetFunctionOption(Constants::Options::CURLOPT_WRITEFUNCTION, writer_func);


		}
		void HandleHeaderFunction(const Request& req){
			cppcomponents::use<Callbacks::HeaderFunction> header_func;
			if (req.HeaderChannel){
				auto chan = req.HeaderChannel;
				auto func = [chan](void* p, std::size_t n, std::size_t nmemb) mutable -> std::size_t{
					auto sz = n*nmemb;
					auto buffer = cppcomponents::Buffer::Create(sz);
					buffer.SetSize(sz);
					std::copy(static_cast<char*>(p), static_cast<char*>(p)+sz, buffer.Begin());
					chan.Write(buffer);
					return sz;
				};

				header_func = cppcomponents::make_delegate<Callbacks::HeaderFunction>(func);

			}
			else{
				auto response_writer = response_.as<IResponseWriter>();
				auto func = [response_writer](void* p, std::size_t n, std::size_t nmemb) mutable -> std::size_t{
					auto sz = n*nmemb;
					response_writer.AddToHeader(static_cast<char*>(p), static_cast<char*>(p)+sz);
					return sz;
				};
                header_func = cppcomponents::make_delegate<Callbacks::HeaderFunction>(func);
			}

			easy_.SetFunctionOption(Constants::Options::CURLOPT_HEADERFUNCTION, header_func);
		}
		void HandleProgressFunction(const Request& req){
			cppcomponents::use<Callbacks::ProgressFunction> progress_func;
			if (req.ProgressChannel){
				auto chan = req.ProgressChannel;
				auto func = [chan](double dltotal, double dlnow, double ultotal, double ulnow) mutable -> std::size_t{

					chan.Write(std::make_tuple(dltotal, dlnow, ultotal, ulnow));
					return 1;
				};

				progress_func = cppcomponents::make_delegate<Callbacks::ProgressFunction>(func);
				easy_.SetFunctionOption(Constants::Options::CURLOPT_PROGRESSFUNCTION, progress_func);

			}
			else{
				easy_.SetInt32Option(Constants::Options::CURLOPT_NOPROGRESS, 1);
			}

		}
	public:
		CurlClient(cppcomponents::use<IMulti> m) :multi_{ m }, easy_{}, response_{ easy_ }
		{}
		CurlClient() :CurlClient{ Curl::DefaultMulti() }
		{}


		cppcomponents::use<IEasy> GetEasy(){
			return easy_;
		}

		cppcomponents::Future<cppcomponents::use<IResponse>> Fetch(){
			auto promise = cppcomponents::make_promise<cppcomponents::use<IResponse>>();
			auto easy = easy_;
			cppcomponents::use<IResponse> response = response_;
			auto completed = [easy, promise, response,this](cppcomponents::use<IEasy>, std::int32_t ec)mutable{
				try{
					CleanupCallbacks(easy);
					if (ec != Constants::Errors::CURLE_OK){
						auto rw = response.QueryInterface<IResponseWriter>();
						rw.SetError(ec);

					}
					if (chan_){
						auto chan = chan_;
						auto done = done_saving_to_file_;
						cppcomponents::async(cppcomponents::asio_runtime::Runtime::GetThreadPool(), [chan,done,promise,response](){chan.Complete(); })
							.Then([chan, done,promise,response](cppcomponents::Future<void> f)mutable{
							if (done){
								done.Then(cppcomponents::asio_runtime::Runtime::GetThreadPool(), [promise, response](cppcomponents::Future<void> f){
									promise.Set(response);
								});
							}
							else{
								promise.Set(response);
							}
						});
					}
					else{

						promise.Set(response);
					}
				}
				catch (std::exception& e)
				{
					//try{
					promise.SetError(cppcomponents::error_mapper::error_code_from_exception(e));
					//}
					//catch (...){}
				}
			};
			multi_.Add(easy_, cppcomponents::make_delegate<Callbacks::CompletedFunction>(completed))
				.Then([promise, easy](cppcomponents::Future<void> f)mutable{
				if (f.ErrorCode() < 0){
					CleanupCallbacks(easy);
					promise.SetError(f.ErrorCode());
				}
			});

			return promise.QueryInterface < cppcomponents::IFuture<cppcomponents::use<IResponse>> >();

		}

		cppcomponents::Future<cppcomponents::use<IResponse>> Fetch(const Request& req){
			easy_.Reset();
			if (!req.Url.size()){ throw cppcomponents::error_invalid_arg(); }
            HandleOptions(req);
			return Fetch();
		}

		cppcomponents::Future<cppcomponents::use<IResponse>> Fetch(const Request& req, cppcomponents::use<IForm> form){
			easy_.Reset();
			if (!req.Url.size()){ throw cppcomponents::error_invalid_arg(); }
			if ((!req.Method.empty()) || (req.Method != "POST")){
				throw cppcomponents::error_invalid_arg();
			}
			easy_.SetPointerOption(Constants::Options::CURLOPT_HTTPPOST, form.get_portable_base());
            HandleOptions(req);
			return Fetch();
		}


	};

}


#endif
