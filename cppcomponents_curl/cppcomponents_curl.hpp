#pragma once
#ifndef INCLUDE_GUARD_cppcomponents_curl_HPP_10_21_2013_
#define INCLUDE_GUARD_cppcomponents_curl_HPP_10_21_2013_

#include <cppcomponents/cppcomponents.hpp>
#include <cppcomponents/future.hpp>
#include <cppcomponents/buffer.hpp>
#include <cppcomponents/channel.hpp>
#include <chrono>

#include "implementation/constants.hpp"
namespace cppcomponents_curl{



	struct ISlist :cppcomponents::define_interface<cppcomponents::uuid<0x66226e79, 0xc3c5, 0x410f, 0xba91, 0xf01b54127ecc>>
	{
		// str must be null-terminated
		void Append(cppcomponents::cr_string str);

		void* GetNative();

		CPPCOMPONENTS_CONSTRUCT(ISlist, Append, GetNative);
	};

	inline std::string slist_id(){ return "cppcomponents_curl_dll!Slist"; }
	typedef cppcomponents::runtime_class<slist_id, cppcomponents::object_interfaces<ISlist>> Slist_t;
	typedef cppcomponents::use_runtime_class<Slist_t> Slist;


	struct IForm :cppcomponents::define_interface<cppcomponents::uuid<0x651ae826, 0xb370, 0x474c, 0x8ad7, 0x704c1195317a>>
	{
		void AddNameValue(cppcomponents::cr_string name, cppcomponents::cr_string value);
		void AddNameFileContents(cppcomponents::cr_string name, cppcomponents::cr_string file);
		void AddFileNoName(cppcomponents::cr_string file);
		void AddFileNoNameWithContentType(cppcomponents::cr_string file, cppcomponents::cr_string content_type);
		void AddFileWithName(cppcomponents::cr_string file, cppcomponents::cr_string filename);
		void AddFileWithNameContentType(cppcomponents::cr_string file, cppcomponents::cr_string filename,cppcomponents::cr_string content_type);

		// buffer must be kept around until after post is complete
		void AddFileAsBuffer(cppcomponents::use<cppcomponents::IBuffer> buffer, cppcomponents::cr_string filename, cppcomponents::cr_string content_type);

		void AddContentHeader(cppcomponents::use<ISlist> list);
		void* GetNative();

		CPPCOMPONENTS_CONSTRUCT(IForm, AddNameValue, AddNameFileContents, AddFileNoName, AddFileNoNameWithContentType,
			AddFileWithName, AddFileWithNameContentType, AddFileAsBuffer, AddContentHeader, GetNative);
	};

	inline std::string form_id(){ return "cppcomponents_curl_dll!Form"; }
	typedef cppcomponents::runtime_class<form_id, cppcomponents::object_interfaces<IForm>> Form_t;
	typedef cppcomponents::use_runtime_class<Form_t> Form;

	struct IEasy :cppcomponents::define_interface<cppcomponents::uuid<0x6182019d, 0x4991, 0x4690, 0x9ee4, 0xf3066ee30e8e>>{
		void SetInt32Option(std::int32_t option, std::int32_t parameter);
		void SetPointerOption(std::int32_t option, void* parameter);
		void SetInt64Option(std::int32_t option, std::int64_t parameter);
		void SetFunctionOption(std::int32_t option, cppcomponents::use<cppcomponents::InterfaceUnknown> function);
		void* GetNative();

		void StorePrivate(const void* key, cppcomponents::use<cppcomponents::InterfaceUnknown>);
		cppcomponents::use<cppcomponents::InterfaceUnknown> GetPrivate(const void* key);
		bool RemovePrivate(const void* key);

		std::int32_t GetInt32Info(std::int32_t info);
		double GetDoubleInfo(std::int32_t info);
		cppcomponents::cr_string GetStringInfo(std::int32_t info);
		std::vector<std::string> GetListInfo(std::int32_t info);

		cppcomponents::cr_string GetErrorDescription();

		void Reset();

		CPPCOMPONENTS_CONSTRUCT(IEasy, SetInt32Option, SetPointerOption, SetInt64Option, SetFunctionOption,StorePrivate,GetPrivate,RemovePrivate, GetNative,
			GetInt32Info,GetDoubleInfo,GetStringInfo,GetListInfo,GetErrorDescription, Reset);

		CPPCOMPONENTS_INTERFACE_EXTRAS(IEasy){

			void SetStringOption(std::int32_t option,cppcomponents::cr_string str){
				const void* p = str.data();
				this->get_interface().SetPointerOption(option,
					const_cast<void*>(p));
			}
		};
	};
	inline std::string easy_id(){ return "cppcomponents_curl_dll!Easy"; }
	typedef cppcomponents::runtime_class<easy_id, cppcomponents::object_interfaces<IEasy>> Easy_t;
	typedef cppcomponents::use_runtime_class<Easy_t> Easy;

	struct IResponse :cppcomponents::define_interface<cppcomponents::uuid<0xd919e330, 0x7ec6, 0x4e7a, 0xa6a7, 0xaedf0b98dc73>>
	{
		cppcomponents::error_code ErrorCode();
		cppcomponents::cr_string ErrorMessage();
		cppcomponents::use<IEasy> Request();
		cppcomponents::cr_string Body();
		std::vector<std::pair<std::string, std::string>> Headers();

		CPPCOMPONENTS_CONSTRUCT(IResponse, ErrorCode, ErrorMessage, Request, Body, Headers);

		CPPCOMPONENTS_INTERFACE_EXTRAS(IResponse){
			std::int32_t ResponseCode(){
				return this->get_interface().Request().GetInt32Info(Constants::Info::CURLINFO_RESPONSE_CODE);
			}

		};
	};

	struct IResponseWriter :cppcomponents::define_interface<cppcomponents::uuid<0x826baf64, 0x1e2e, 0x401e, 0xbccc, 0x14227dda0fbe>>
	{
		void AddToBody(const char* first, const char* last);

		void AddToHeader(const char* first, const char* last);

		void SetError(cppcomponents::error_code ec);

		CPPCOMPONENTS_CONSTRUCT(IResponseWriter, AddToBody, AddToHeader, SetError);

	};

	struct IResponseFactory :cppcomponents::define_interface<cppcomponents::uuid<0x71163bc4, 0x95ba, 0x49f8, 0x9263, 0x28d366ab7467>>
	{
		cppcomponents::use<cppcomponents::InterfaceUnknown> Create(cppcomponents::use<IEasy>);

		CPPCOMPONENTS_CONSTRUCT(IResponseFactory, Create);
	};
	inline std::string response_id(){ return "cppcomponents_curl_dll!Response"; }
	typedef cppcomponents::runtime_class<response_id, cppcomponents::object_interfaces<IResponse,IResponseWriter>
	,cppcomponents::factory_interface<IResponseFactory>> Response_t;
	typedef cppcomponents::use_runtime_class<Response_t> Response;

	namespace Callbacks{
		typedef cppcomponents::delegate<void(cppcomponents::use<IEasy>, std::int32_t ec)> CompletedFunction;
	}

	struct IMulti :cppcomponents::define_interface<cppcomponents::uuid<0xc05815c2, 0xef99, 0x40cb, 0xafe5, 0x35cafdefe834>>{
		cppcomponents::Future<void> Add(cppcomponents::use<IEasy>,cppcomponents::use<Callbacks::CompletedFunction>);
		cppcomponents::Future<void>  Remove(cppcomponents::use<IEasy>);
		void* GetNative();

		CPPCOMPONENTS_CONSTRUCT(IMulti, Add, Remove,GetNative);

	};

	struct ICurlStatics : cppcomponents::define_interface<cppcomponents::uuid<0x97460a91, 0x62f8, 0x4788, 0x8ba9, 0x7a3d162b5a03>>{
		std::string Escape(cppcomponents::cr_string url);
		std::string UnEscape(cppcomponents::cr_string url);
		cppcomponents::cr_string Version();
		std::chrono::system_clock::time_point GetDate(cppcomponents::cr_string date);
		cppcomponents::use<IMulti> DefaultMulti();

		CPPCOMPONENTS_CONSTRUCT(ICurlStatics, Escape, UnEscape, Version, GetDate, DefaultMulti);

	};

	inline std::string curlstatics_id(){ return "cppcomponents_curl_dll!Curl"; }
	typedef cppcomponents::runtime_class<curlstatics_id, cppcomponents::static_interfaces<ICurlStatics>> Curl_t;
	typedef cppcomponents::use_runtime_class<Curl_t> Curl;



	namespace Callbacks{

		typedef cppcomponents::delegate < std::size_t(char* ptr, std::size_t size,
			std::size_t nmemb)> WriteFunction;
		typedef cppcomponents::delegate < std::size_t(void* ptr, std::size_t size,
			std::size_t nmemb)> ReadFunction;
		typedef cppcomponents::delegate < std::size_t(double dltotal, double dlnow, 
			double ultotal, double ulnow)> ProgressFunction;
		typedef cppcomponents::delegate < std::size_t(void* ptr, std::size_t size,
			std::size_t nmemb)> HeaderFunction;




	}




}



#endif