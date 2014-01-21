#include "../cppcomponents_curl/cppcomponents_curl.hpp"
#include <curl/curl.h>

#include <cppcomponents_asio_runtime/cppcomponents_asio_runtime.hpp>

#include <array>
#include <algorithm>
#include <map>

#include <thread>


using namespace cppcomponents;
using namespace cppcomponents::asio_runtime;

using namespace cppcomponents_curl;


inline void curl_throw_if_error(CURLFORMcode code){
	if (code != CURL_FORMADD_OK){
		throw_if_error(-static_cast<error_code>(code));
	}
}


inline void curl_throw_if_error(CURLcode code){
	if (code != CURLE_OK){
		throw_if_error(-static_cast<error_code>(code));
	}
}
inline void curl_throw_if_error(CURLMcode code){
	if (code != CURLM_OK){
		throw_if_error(-static_cast<error_code>(code));
	}
}


struct ImpSlist :implement_runtime_class<ImpSlist, Slist_t>{

	curl_slist* list_;

	ImpSlist() :list_{ nullptr }{}

	~ImpSlist(){
		if (!list_){
			curl_slist_free_all(list_);
		}
	}

	void Append(cppcomponents::cr_string str){
		list_ = curl_slist_append(list_, str.data());
		if (!list_){
			throw error_fail();
		}
	}

	void* GetNative(){
		return list_;
	}
};

CPPCOMPONENTS_REGISTER(ImpSlist);

struct ImpForm :implement_runtime_class<ImpForm, Form_t>{

	curl_httppost* first_;
	curl_httppost* last_;

	ImpForm() :first_{ nullptr }, last_{ nullptr }{}

	~ImpForm(){
		if (first_){
			curl_formfree(first_);
		}
	}

	void AddNameValue(cppcomponents::cr_string name, cppcomponents::cr_string value){
		auto res = curl_formadd(&first_, &last_,
			CURLFORM_COPYNAME, name.data(),
			CURLFORM_NAMELENGTH, (long)name.size(),
			CURLFORM_COPYCONTENTS, value.data(),
			CURLFORM_CONTENTSLENGTH, (long)value.size(),
			CURLFORM_END);
		curl_throw_if_error(res);
	}
	void AddNameFileContents(cppcomponents::cr_string name, cppcomponents::cr_string file){
		auto res = curl_formadd(&first_, &last_,
			CURLFORM_COPYNAME, name.data(),
			CURLFORM_NAMELENGTH, (long)name.size(),
			CURLFORM_FILECONTENT, file.data(),
			CURLFORM_END);

		curl_throw_if_error(res);

	}
	void AddFileNoName(cppcomponents::cr_string file){
		auto res = curl_formadd(&first_, &last_,
			CURLFORM_FILE, file.data(),
			CURLFORM_END);

		curl_throw_if_error(res);

	}
	void AddFileNoNameWithContentType(cppcomponents::cr_string file, cppcomponents::cr_string content_type){
		auto res = curl_formadd(&first_, &last_,
			CURLFORM_FILE, file.data(),
			CURLFORM_CONTENTTYPE, content_type.data(),
			CURLFORM_END);

		curl_throw_if_error(res);

	}
	void AddFileWithName(cppcomponents::cr_string file, cppcomponents::cr_string filename){
		auto res = curl_formadd(&first_, &last_,
			CURLFORM_FILE, file.data(),
			CURLFORM_FILENAME, filename.data(),
			CURLFORM_END);

		curl_throw_if_error(res);

	}
	void AddFileWithNameContentType(cppcomponents::cr_string file, cppcomponents::cr_string filename, cppcomponents::cr_string content_type){
		auto res = curl_formadd(&first_, &last_,
			CURLFORM_FILE, file.data(),
			CURLFORM_CONTENTTYPE, content_type.data(),
			CURLFORM_FILENAME, filename.data(),
			CURLFORM_END);

		curl_throw_if_error(res);
	}

	// buffer must be kept around until after post is complete
	void AddFileAsBuffer(cppcomponents::use<cppcomponents::IBuffer> buffer, cppcomponents::cr_string filename, cppcomponents::cr_string content_type){
		auto res = curl_formadd(&first_, &last_,
			CURLFORM_BUFFERPTR, buffer.Begin(),
			CURLFORM_BUFFERLENGTH, (long)buffer.Size(),
			CURLFORM_CONTENTTYPE, content_type.data(),
			CURLFORM_BUFFER, filename.data(),
			CURLFORM_END);

		curl_throw_if_error(res);

	}

	void AddContentHeader(cppcomponents::use<ISlist> list){
		auto res = curl_formadd(&first_, &last_,
			CURLFORM_CONTENTHEADER, list.GetNative(),
			CURLFORM_END);

		curl_throw_if_error(res);

	}

	void* GetNative(){
		return first_;
	}
};

CPPCOMPONENTS_REGISTER(ImpForm)

template<class Delegate>
 use<cppcomponents::delegate<Delegate>> DelegateFromVoid(void* userdata){
	// user data is the delegate pointer
	use<InterfaceUnknown> iunk{ cppcomponents::reinterpret_portable_base<InterfaceUnknown>(
		static_cast<portable_base*>(userdata)), true };
	return iunk.QueryInterface<Delegate>();
}
 struct IImp :define_interface<cppcomponents::uuid<0xd9185c90, 0xd32e, 0x4909, 0xafaa, 0xc9a50557ae28>>
 {
	 void* GetImp();

	 CPPCOMPONENTS_CONSTRUCT(IImp, GetImp);
 };

 inline std::string easyimp_id(){ return "cppcomponents_curl_dll!Easy"; }
 typedef cppcomponents::runtime_class<easyimp_id, cppcomponents::object_interfaces<IEasy,IImp>> EasyWithImp_t;
 typedef cppcomponents::use_runtime_class<EasyWithImp_t> EasyWithImp;;

 struct ImpEasy :implement_runtime_class<ImpEasy, EasyWithImp_t>
 {
	 CURL* easy_;


	 use<IForm> form_;

	 std::array<char, CURL_ERROR_SIZE + 1> error_buffer_;

	 use<Callbacks::WriteFunction> write_function_;
	 use<Callbacks::ReadFunction> read_function_;
	 use<Callbacks::HeaderFunction> header_function_;
	 use<Callbacks::ProgressFunction> progress_function_;

	 std::map < const void*, use<InterfaceUnknown> > extra_info_;

	static ImpEasy* impeasy_from_easy(CURL* easy){
		 char* charpeasy = 0;
		 curl_easy_getinfo(easy, CURLINFO_PRIVATE, &charpeasy);
		 void* vpeasy = charpeasy;
		 auto iunk = use<InterfaceUnknown>{reinterpret_portable_base<InterfaceUnknown>(static_cast<portable_base*>(vpeasy)), true};
		 return static_cast<ImpEasy*>(iunk.QueryInterface<IImp>().GetImp());
	 }


	void* IImp_GetImp(){
		return this;
	}

	void Init(){

		 // Set the private of easy to interface
		 auto res = curl_easy_setopt(easy_, CURLOPT_PRIVATE, this->get_unknown_portable_base());
		 curl_throw_if_error(res);
		 
		 std::fill(error_buffer_.begin(), error_buffer_.end(), 0);
		 curl_easy_setopt(easy_, CURLOPT_ERRORBUFFER, error_buffer_.data());
	}

	 ImpEasy()
		 :
		 easy_{ curl_easy_init() }
	 {
		 if (!easy_){
			 throw error_fail();
		 }

	 }

	 ~ImpEasy(){
		 if (easy_){
			 curl_easy_cleanup(easy_);
		 }
	 }
	 void SetInt32Option(std::int32_t option, std::int32_t parameter){
		 auto res = curl_easy_setopt(easy_, static_cast<CURLoption>(option), (long)parameter);
		 curl_throw_if_error(res);

	 }
	 void SetPointerOption(std::int32_t option, void* parameter){
		 if (option == CURLOPT_WRITEDATA ||
			 option == CURLOPT_READDATA ||
			 option == CURLOPT_PROGRESSDATA ||
			 option == CURLOPT_HEADERDATA ||
			 option == CURLOPT_PRIVATE ||
			 option == CURLOPT_ERRORBUFFER
			 )
		 {

			 throw error_invalid_arg();
		 }
		 if (option == CURLOPT_HTTPPOST){
			 auto pb = static_cast<portable_base*>(parameter);
			 use<InterfaceUnknown> iunk{ cppcomponents::reinterpret_portable_base<InterfaceUnknown>(pb), true };
			 form_ = iunk.QueryInterface<IForm>();
			 auto res = curl_easy_setopt(easy_, static_cast<CURLoption>(option), static_cast<void*>(form_.GetNative()));
			 curl_throw_if_error(res);

		 }
		 else if (option == CURLOPT_HEADER){
			 if (parameter == nullptr){
				 auto res = curl_easy_setopt(easy_, static_cast<CURLoption>(option), nullptr);
				 curl_throw_if_error(res);

			 }
			 else{
				 auto pb = static_cast<portable_base*>(parameter);
				 use<InterfaceUnknown> iunk{ cppcomponents::reinterpret_portable_base<InterfaceUnknown>(pb), true };
				 auto slist = iunk.QueryInterface<ISlist>();
				 auto res = curl_easy_setopt(easy_, static_cast<CURLoption>(option), static_cast<void*>(slist.GetNative()));
				 curl_throw_if_error(res);
			 }

		 }
		 auto res = curl_easy_setopt(easy_, static_cast<CURLoption>(option), parameter);
		 curl_throw_if_error(res);

	 }
	 void SetInt64Option(std::int32_t option, std::int64_t parameter){
		 auto res = curl_easy_setopt(easy_, static_cast<CURLoption>(option), (curl_off_t)parameter);
		 curl_throw_if_error(res);

	 }

	 static std::size_t WriteFunctionRaw(char* ptr, std::size_t size, std::size_t nmemb, void* userdata){

		 auto& imp = *static_cast<ImpEasy*>(userdata);
		 if (imp.write_function_)
			 return imp.write_function_(ptr, size, nmemb);
		 return 0;
	 }
	 static std::size_t ReadFunctionRaw(void* ptr, std::size_t size, std::size_t nmemb, void* userdata){
		 auto& imp = *static_cast<ImpEasy*>(userdata);
		 if (imp.read_function_)
			 return imp.read_function_(ptr, size, nmemb);
		 return 0;
	 }
	 static std::size_t HeaderFunctionRaw(void* ptr, std::size_t size, std::size_t nmemb, void* userdata){
		 auto& imp = *static_cast<ImpEasy*>(userdata);
		 if (imp.header_function_)
			 return imp.header_function_(ptr, size, nmemb);
		 return 0;
	 }

	 static int ProgressFunctionRaw(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow){
		 auto& imp = *static_cast<ImpEasy*>(clientp);
		 if (imp.progress_function_)
			 return imp.progress_function_(dltotal, dlnow, ultotal, ulnow);
		 return 0;

	 }

	 template<class T>
	 void SetFunctionData(CURLoption data, CURLoption function, T f){
		 void* pthis = this;
		 curl_easy_setopt(easy_,data, pthis);
		 curl_easy_setopt(easy_, function, f);
	 }

	 void SetFunctionOption(std::int32_t option, cppcomponents::use<cppcomponents::InterfaceUnknown> function){

		 if (option == CURLOPT_WRITEFUNCTION){
			 SetFunctionData(CURLOPT_WRITEDATA, CURLOPT_WRITEFUNCTION, WriteFunctionRaw);
			 if (function){
				 write_function_ = function.QueryInterface<Callbacks::WriteFunction>();

			 }
			 else{
				 write_function_ = nullptr;
			 }
		 }
		 else if (option == CURLOPT_READFUNCTION){
			 SetFunctionData(CURLOPT_READDATA, CURLOPT_READFUNCTION, ReadFunctionRaw);
			 if (function){
				 read_function_ = function.QueryInterface<Callbacks::ReadFunction>();

			 }
			 else{
				 read_function_ = nullptr;
			 }
		 }
		 else if (option == CURLOPT_PROGRESSFUNCTION){
			 SetFunctionData(CURLOPT_PROGRESSDATA, CURLOPT_PROGRESSFUNCTION,ProgressFunctionRaw);
			 if (function){
				 progress_function_ = function.QueryInterface<Callbacks::ProgressFunction>();
			 }
			 else{
				 progress_function_ = nullptr;
			 }
		 }
		 else if (option == CURLOPT_HEADERFUNCTION){
			 SetFunctionData(CURLOPT_HEADERDATA, CURLOPT_HEADERFUNCTION,HeaderFunctionRaw);
			 if (function){
				 header_function_ = function.QueryInterface<Callbacks::HeaderFunction>();
			 }
			 else{
				 header_function_ = nullptr;
			 }
		 }
		 else{
			 throw error_invalid_arg();
		 }
	 }
	 void* GetNative(){
		 return easy_;
	 }

	 void StorePrivate(const void* key, cppcomponents::use<InterfaceUnknown> v){
		 extra_info_[key] = v;
	 }
	 cppcomponents::use<InterfaceUnknown> GetPrivate(const void* key){
		 auto iter = extra_info_.find(key);
		 if (iter == extra_info_.end()){
			 return nullptr;
		 }
		 return iter->second;
	 }

	 bool RemovePrivate(const void* key){
		 return extra_info_.erase(key) > 0;
	 }



	 std::int32_t GetInt32Info(std::int32_t info){
		 long result{};
		 auto res = curl_easy_getinfo(easy_, static_cast<CURLINFO>(info), &result);
		 curl_throw_if_error(res);
		 return result;
	 }
	 double GetDoubleInfo(std::int32_t info){
		 double result{};
		 auto res = curl_easy_getinfo(easy_, static_cast<CURLINFO>(info), &result);
		 curl_throw_if_error(res);
		 return result;

	 }
	 cppcomponents::cr_string GetStringInfo(std::int32_t info){
		 char* result{};
		 auto res = curl_easy_getinfo(easy_, static_cast<CURLINFO>(info), &result);
		 curl_throw_if_error(res);
		 return cr_string{ result };

	 }
	 std::vector<std::string> GetListInfo(std::int32_t info){
		 curl_slist* result{};
		 auto res = curl_easy_getinfo(easy_, static_cast<CURLINFO>(info), &result);
		 curl_throw_if_error(res);
		 if (!result){
			 throw error_fail();
		 }
		 try{
			 std::vector<std::string> vec;
			 for (auto node = result; node != nullptr; node = node->next){
				 vec.push_back(node->data);
			 }
			 return vec;
		 }
		 catch (...){
			 curl_slist_free_all(result);
			 throw;
		 }
	 }

	 cppcomponents::cr_string GetErrorDescription(){
		 return cr_string{ error_buffer_.data() };
	 }


	 void Reset(){
		 curl_easy_reset(easy_);
		 Init();
	 }


};

CPPCOMPONENTS_REGISTER(ImpEasy)


inline std::string multi_id(){ return "cppcomponents_curl_dll!Multi"; }
typedef cppcomponents::runtime_class<multi_id, cppcomponents::object_interfaces<IMulti, IImp>> Multi_t;
typedef cppcomponents::use_runtime_class<Multi_t> Multi;


//inline std::string response_id(){ return "cppcomponents_curl_dll!Response"; }
//typedef cppcomponents::runtime_class<response_id, cppcomponents::object_interfaces<IResponse, IImp>,factory_interface<NoConstructorFactoryInterface>> Response_t;
//typedef cppcomponents::use_runtime_class<Response_t> Response;


struct ImpResponse :implement_runtime_class<ImpResponse, Response_t>
{
	use<IEasy> easy_;
	std::vector<char> body_;
	std::vector<std::pair<std::string, std::string>> headers_;
	cppcomponents::error_code ec_;

	ImpResponse(use<IEasy> e) :easy_{ e }, ec_{ 0 }{}

	void IResponseWriter_AddToBody(const char* first, const char* last){
		body_.insert(body_.end(), first, last);
	}

	void IResponseWriter_AddToHeader(const char* first, const char* last){
        if ((last - first) == 2){
            if (*first == '\r' && *(first + 1) == '\n'){
                return;
            }
        }
		auto colon = std::find(first, last, ':');
		std::string name{ first, colon };
		if (colon != last){
			++colon;
		}
        static char rn[] = { '\r', '\n' }; 
		std::string value{ colon, std::search(colon,last,rn,rn+2) };
		headers_.push_back(std::make_pair(name, value));
	}
	
	void IResponseWriter_SetError(cppcomponents::error_code ec){
		if (ec < 0){
			ec_ = ec;
		}
		else{
			ec_ = -ec;
		}
	}

	void* IImp_GetImp(){
		return this;
	}

	cppcomponents::error_code ErrorCode(){
		return ec_;
	}

	cppcomponents::cr_string ErrorMessage(){
		return easy_.GetErrorDescription();
	}

	cppcomponents::use<IEasy> Request(){
		return easy_;
	}
	cppcomponents::cr_string Body(){
		throw_if_error(ec_);
		if (!body_.size()){
			return cr_string{};
		}
		return cr_string{ &body_[0], body_.size() };
	}

	std::vector<std::pair<std::string, std::string>> Headers(){
		throw_if_error(ec_);
		return headers_;
	}


};
CPPCOMPONENTS_REGISTER(ImpResponse)


//struct ImpMulti :implement_runtime_class<ImpMulti, Multi_t>
//{
//	static const int pollid = 0;
//	static const int callbackid = 0;
//	static const int selfid = 0;
//	bool own_executor_;
//	use<uv::IUvExecutor> executor_;
//	std::thread thread_;
//
//	CURLM* multi_;
//
//	use<uv::ITimer> timeout_;
//
//	static use<IEasy> ieasy_from_easy(CURL* easy){
//		char* charpeasy = 0;
//		curl_easy_getinfo(easy, CURLINFO_PRIVATE, &charpeasy);
//		void* vpeasy = charpeasy;
//		auto iunk = use<InterfaceUnknown>{reinterpret_portable_base<InterfaceUnknown>(static_cast<portable_base*>(vpeasy)), true};
//		return iunk.QueryInterface<IEasy>();
//	}
//
//	static void curl_perform(use<uv::IPoll>, int status, int events, curl_socket_t sockfd, ImpMulti* pthis)
//	{
//		int running_handles;
//		int flags = 0;
//		char *done_url;
//		CURLMsg *message;
//		int pending;
//		pthis->timeout_.Stop();
//
//		if (events & uv::Constants::PollEvent::Readable)
//			flags |= CURL_CSELECT_IN;
//		if (events & uv::Constants::PollEvent::Writable)
//			flags |= CURL_CSELECT_OUT;
//
//
//
//		curl_multi_socket_action(pthis->multi_, sockfd, flags,
//			&running_handles);
//
//		while ((message = curl_multi_info_read(pthis->multi_, &pending))) {
//
//
//			switch (message->msg) {
//			case CURLMSG_DONE:
//			{
//								 curl_easy_getinfo(message->easy_handle, CURLINFO_EFFECTIVE_URL,
//									 &done_url);
//								 auto easy = message->easy_handle;
//								 auto ieasy = ieasy_from_easy(easy);
//
//								 pthis->RemoveAndCallCallback(ieasy, message->data.result);
//
//			}
//
//				break;
//			default:
//				fprintf(stderr, "CURLMSG default\n");
//				abort();
//			}
//		}
//	}
//
//
//
//	static void start_timeout(CURLM *multi, long timeout_ms, void *userp)
//	{
//		try{
//
//			auto pthis = static_cast<ImpMulti*>(userp);
//			auto& timeout = pthis->timeout_;
//            if (timeout_ms <= 0){
//                int running_handles;
//                curl_multi_socket_action(multi, CURL_SOCKET_TIMEOUT, 0,
//                    &running_handles);
//                int pending = 0;
//                CURLMsg * message = nullptr;
//                while ((message = curl_multi_info_read(pthis->multi_, &pending))) {
//
//
//                    switch (message->msg) {
//                    case CURLMSG_DONE:
//                    {
//
//                                         auto easy = message->easy_handle;
//                                         auto ieasy = ieasy_from_easy(easy);
//
//                                         pthis->RemoveAndCallCallback(ieasy, message->data.result);
//
//                    }
//
//                        break;
//                    default:
//                        fprintf(stderr, "CURLMSG default\n");
//                        abort();
//                    }
//                }
//                return;
//            }
//
//			timeout.Start([multi](use<uv::ITimer>, int status){
//				int running_handles;
//				curl_multi_socket_action(multi, CURL_SOCKET_TIMEOUT, 0,
//					&running_handles);
//			}, std::chrono::milliseconds{ timeout_ms });
//		}
//		catch (...){
//			// swallow exceptions
//			int running_handles;
//			curl_multi_socket_action(multi, CURL_SOCKET_TIMEOUT, CURL_CSELECT_ERR,
//				&running_handles);
//		}
//	}
//
//	static int handle_socket(CURL *easy, curl_socket_t s, int action, void *userp,
//		void *)
//	{
//		try{
//
//
//			auto pthis = static_cast<ImpMulti*>(userp);
//			auto ieasy = ieasy_from_easy(easy);
//			auto iunkpoll = ieasy.GetPrivate(&pollid);
//			use<uv::IPoll> poll;
//		
//			if (action == CURL_POLL_IN || action == CURL_POLL_OUT) {
//				if (!iunkpoll) {
//					poll = uv::Poll{ pthis->executor_.GetLoop(), s, false };
//					ieasy.StorePrivate(&pollid, poll);
//				}
//				else{
//					poll = iunkpoll.QueryInterface<uv::IPoll>();
//
//				}
//			}
//
//			switch (action) {
//			case CURL_POLL_IN:
//				using namespace std::placeholders;
//				poll.Start(uv::Constants::PollEvent::Readable, std::bind(curl_perform, _1, _2, _3, s,pthis));
//				break;
//			case CURL_POLL_OUT:
//				poll.Start(uv::Constants::PollEvent::Writable, std::bind(curl_perform, _1, _2, _3, s,pthis));
//
//
//				break;
//			case CURL_POLL_REMOVE:
//				if (poll) {
//					poll.Stop();
//					ieasy.RemovePrivate(&pollid);
//				}
//				break;
//			default:
//				return -1;
//			}
//
//			return 0;
//
//		}
//		catch (...){
//			return -1;
//			// swallow exceptions
//		}
//	}
//
//	void Setup(){
//		multi_ = curl_multi_init();
//		if (!multi_){
//			throw error_fail();
//		}
//		curl_multi_setopt(multi_, CURLMOPT_SOCKETFUNCTION, handle_socket);
//		curl_multi_setopt(multi_, CURLMOPT_SOCKETDATA, static_cast<void*>(this));
//		curl_multi_setopt(multi_, CURLMOPT_TIMERFUNCTION, start_timeout);
//		curl_multi_setopt(multi_, CURLMOPT_TIMERDATA, static_cast<void*>(this));
//		timeout_ = uv::Timer{ executor_.GetLoop() };
//	}
//
//	ImpMulti(use<InterfaceUnknown> executor = nullptr) 
//		:own_executor_{!executor},
//		executor_{ own_executor_ ? uv::Executor{} : executor.QueryInterface<uv::IUvExecutor>() }
//	{
//		use<IMulti> self = QueryInterface<IMulti>();
//		executor_.Add([this,self]()mutable{
//			Setup();
//		});
//		if (own_executor_){
//			auto exec = executor_;
//			auto threadfunc = [this,exec]()mutable{
//				exec.Loop();
//				exec = nullptr;
//			};
//			thread_ = std::thread{ threadfunc };
//		}
//
//
//		return;
//
//	}
//	void ReleaseImplementationDestroy(){
//		auto multi = multi_;
//		timeout_ = nullptr;
//		auto exec = executor_;
//		executor_ = nullptr;
//		exec.Add([multi,exec]()mutable{
//			curl_multi_cleanup(multi);
//			multi = nullptr;
//			exec.MakeLoopExit();
//			exec = nullptr;
//		});
//		if (own_executor_){
//			thread_.join();
//		}
//		auto i = exec.NumPendingClosures();
//		for (; i > 0; i = exec.NumPendingClosures()){
//			exec.RunQueuedClosures();
//		}
//		exec = nullptr;
//		delete this;
//	}
//	~ImpMulti(){
//	}
//
//	void RemovePrivate(cppcomponents::use<IEasy>& easy){
//			easy.RemovePrivate(&callbackid);
//			easy.RemovePrivate(&pollid);
//			easy.RemovePrivate(&selfid);
//	}
//
//	Future<void> Add(cppcomponents::use<IEasy> easy, cppcomponents::use<Callbacks::CompletedFunction> func){
//		auto promise = make_promise<void>();
//		use<IMulti> self = QueryInterface<IMulti>();
//		auto closure = [self,promise,this, easy, func]()mutable{
//			// Store the promise
//			try{
//
//				easy.StorePrivate(&callbackid, func);
//				easy.StorePrivate(&selfid, self);
//				auto res = curl_multi_add_handle(multi_, static_cast<CURL*>(easy.GetNative()));
//				curl_throw_if_error(res);
//				promise.Set();
//			}
//			catch (...){
//				RemovePrivate(easy);
//
//				promise.SetError(error_fail::ec);
//			}
//		};
//
//		executor_.Add(closure);
//
//		return promise.QueryInterface<IFuture<void>>();
//
//	}
//	template<class I>
//	use<I> GetPrivateSafe(use<IEasy>& easy, const void* key){
//		auto iunk = easy.GetPrivate(key);
//		if (!iunk){
//			throw error_fail();
//		}
//		return iunk.QueryInterface<I>();
//	}
//	void RemoveAndCallCallback(use<IEasy> easy, CURLcode code){
//		auto res = curl_multi_remove_handle(multi_, static_cast<CURL*>(easy.GetNative()));
//		curl_throw_if_error(res);
//		auto func = GetPrivateSafe<Callbacks::CompletedFunction>(easy, &callbackid);
//		RemovePrivate(easy);
//		func(easy, code);
//
//	}
//	Future<void> Remove(cppcomponents::use<IEasy> easy){
//		auto promise = make_promise<void>();
//		auto closure = [promise, this, easy]()mutable{
//
//			RemoveAndCallCallback(easy, CURLE_OK);
//		};
//		executor_.Add(closure);
//
//		return promise.QueryInterface<IFuture<void>>();
//	}
//	void* GetNative(){
//		return multi_;
//	}
//
//
//
//
//	void* IImp_GetImp(){
//		return this;
//
//	}
//};
//
//CPPCOMPONENTS_REGISTER(ImpMulti)

struct curl_freer{
	void* p_;
	curl_freer(void* p) :p_(p){}
	~curl_freer(){
		if (p_){
			curl_free(p_);
		}
	}
};

struct ImpCurlStatics : implement_runtime_class<ImpCurlStatics, Curl_t>
{
	ImpCurlStatics(){}
	static std::string Escape(cppcomponents::cr_string url){
		auto c = curl_escape(url.data(), url.size());
		curl_freer f{ c };
		if (!c){
			throw error_fail();
		}
		std::string ret{ c };
		return ret;
	}
	static std::string UnEscape(cppcomponents::cr_string url){
		auto c = curl_unescape(url.data(), url.size());
		curl_freer f{ c };
		if (!c){
			throw error_fail();
		}
		std::string ret{ c };
		return ret;
	}
	static cppcomponents::cr_string Version(){
		return cr_string{ curl_version() };
	}
	static std::chrono::system_clock::time_point GetDate(cppcomponents::cr_string date){
		auto t = curl_getdate(date.data(),nullptr);
		return std::chrono::system_clock::from_time_t(t);
	}
	static cppcomponents::use<IMulti> DefaultMulti(){
		struct uniq{};
		return cross_compiler_interface::detail::safe_static_init<Multi, uniq>::get();

	}


};

CPPCOMPONENTS_REGISTER(ImpCurlStatics)

struct CurlInit{
	CurlInit(){
		curl_global_init(CURL_GLOBAL_ALL);
	}

	~CurlInit(){
		curl_global_cleanup();
	}
};

CurlInit curlinit_;


CPPCOMPONENTS_DEFINE_FACTORY()
