









#pragma once

#include "HiveBlueprintLibrary.h"



struct FHiveadmin_session_AdminSession DeserializeFHiveadmin_session_AdminSession(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveadmin_session_AdminSession Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_username;
	if (obj->TryGetStringField(TEXT("username"), F_username))
	{
		Target.username = F_username;
	}

	double F_expiry;
	if (obj->TryGetNumberField(TEXT("expiry"), F_expiry))
	{
		Target.expiry = (int32)F_expiry;
	}

	FString F_project;
	if (obj->TryGetStringField(TEXT("project"), F_project))
	{
		Target.project = F_project;
	}


	return Target;
}



struct FHiveadmin_session_AdminSessionWithSecrets DeserializeFHiveadmin_session_AdminSessionWithSecrets(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveadmin_session_AdminSessionWithSecrets Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_username;
	if (obj->TryGetStringField(TEXT("username"), F_username))
	{
		Target.username = F_username;
	}

	double F_expiry;
	if (obj->TryGetNumberField(TEXT("expiry"), F_expiry))
	{
		Target.expiry = (int32)F_expiry;
	}

	FString F_project;
	if (obj->TryGetStringField(TEXT("project"), F_project))
	{
		Target.project = F_project;
	}

	FString F_apiKey;
	if (obj->TryGetStringField(TEXT("apiKey"), F_apiKey))
	{
		Target.apiKey = F_apiKey;
	}

	FString F_secretKey;
	if (obj->TryGetStringField(TEXT("secretKey"), F_secretKey))
	{
		Target.secretKey = F_secretKey;
	}


	return Target;
}



struct FHiveadmin_session_AdminUserSummary DeserializeFHiveadmin_session_AdminUserSummary(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveadmin_session_AdminUserSummary Target;
	

	FString F_username;
	if (obj->TryGetStringField(TEXT("username"), F_username))
	{
		Target.username = F_username;
	}


	return Target;
}



struct FHiveadmin_session_Project DeserializeFHiveadmin_session_Project(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveadmin_session_Project Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_name;
	if (obj->TryGetStringField(TEXT("name"), F_name))
	{
		Target.name = F_name;
	}

	bool F_active;
	if (obj->TryGetBoolField(TEXT("active"), F_active))
	{
		Target.active = (bool)F_active;
	}


	return Target;
}



struct FHiveadmin_session_ProjectAccessEntry DeserializeFHiveadmin_session_ProjectAccessEntry(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveadmin_session_ProjectAccessEntry Target;
	

	FString F_type;
	if (obj->TryGetStringField(TEXT("type"), F_type))
	{
		Target.type = F_type;
	}

	FString F_username;
	if (obj->TryGetStringField(TEXT("username"), F_username))
	{
		Target.username = F_username;
	}

	FString F_projectId;
	if (obj->TryGetStringField(TEXT("projectId"), F_projectId))
	{
		Target.projectId = F_projectId;
	}

	FString F_projectName;
	if (obj->TryGetStringField(TEXT("projectName"), F_projectName))
	{
		Target.projectName = F_projectName;
	}


	return Target;
}



Uadmin_session_AdministrationSession_sessionGET::Uadmin_session_AdministrationSession_sessionGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_AdministrationSession_sessionGET* Uadmin_session_AdministrationSession_sessionGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uadmin_session_AdministrationSession_sessionGET* Proxy = NewObject<Uadmin_session_AdministrationSession_sessionGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uadmin_session_AdministrationSession_sessionGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /session get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/session?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_AdministrationSession_sessionGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /session get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_AdminSession(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /session get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_AdministrationSession_sessionGET>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_AdministrationSession_sessionPUT::Uadmin_session_AdministrationSession_sessionPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_AdministrationSession_sessionPUT* Uadmin_session_AdministrationSession_sessionPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString username

	, FString password

	, FString project
)
{
	Uadmin_session_AdministrationSession_sessionPUT* Proxy = NewObject<Uadmin_session_AdministrationSession_sessionPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_username = username;

	Proxy->Field_password = password;

	Proxy->Field_project = project;


	return Proxy;
}

void Uadmin_session_AdministrationSession_sessionPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /session put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/session?username=%s&password=%s&project=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_username)

		, *FGenericPlatformHttp::UrlEncode(this->Field_password)

		, *FGenericPlatformHttp::UrlEncode(this->Field_project)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_AdministrationSession_sessionPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /session put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_AdminSessionWithSecrets(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /session put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_AdministrationSession_sessionPUT>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_AdministrationSession_sessionPOST::Uadmin_session_AdministrationSession_sessionPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_AdministrationSession_sessionPOST* Uadmin_session_AdministrationSession_sessionPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uadmin_session_AdministrationSession_sessionPOST* Proxy = NewObject<Uadmin_session_AdministrationSession_sessionPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uadmin_session_AdministrationSession_sessionPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /session post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/session?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_AdministrationSession_sessionPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /session post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_AdminSession(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /session post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSession(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_AdministrationSession_sessionPOST>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_AdministrationSession_sessionDELETE::Uadmin_session_AdministrationSession_sessionDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_AdministrationSession_sessionDELETE* Uadmin_session_AdministrationSession_sessionDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uadmin_session_AdministrationSession_sessionDELETE* Proxy = NewObject<Uadmin_session_AdministrationSession_sessionDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uadmin_session_AdministrationSession_sessionDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /session delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/session?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_AdministrationSession_sessionDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /session delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /session delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /session delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /session delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_AdministrationSession_sessionDELETE>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_AdministrationSession_switchPUT::Uadmin_session_AdministrationSession_switchPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_AdministrationSession_switchPUT* Uadmin_session_AdministrationSession_switchPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uadmin_session_AdministrationSession_switchPUT* Proxy = NewObject<Uadmin_session_AdministrationSession_switchPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uadmin_session_AdministrationSession_switchPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /switch put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/switch?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_AdministrationSession_switchPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /switch put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /switch put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /switch put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /switch put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /switch put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /switch put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_AdminSessionWithSecrets(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /switch put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /switch put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminSessionWithSecrets(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_AdministrationSession_switchPUT>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_AdministrationUser_userGET::Uadmin_session_AdministrationUser_userGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_AdministrationUser_userGET* Uadmin_session_AdministrationUser_userGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString username
)
{
	Uadmin_session_AdministrationUser_userGET* Proxy = NewObject<Uadmin_session_AdministrationUser_userGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_username = username;


	return Proxy;
}

void Uadmin_session_AdministrationUser_userGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /user get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/user?username=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_username)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_AdministrationUser_userGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /user get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_AdminUserSummary(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /user get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_AdministrationUser_userGET>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_AdministrationUser_userPUT::Uadmin_session_AdministrationUser_userPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_AdministrationUser_userPUT* Uadmin_session_AdministrationUser_userPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString username

	, FString password

	, FString email
)
{
	Uadmin_session_AdministrationUser_userPUT* Proxy = NewObject<Uadmin_session_AdministrationUser_userPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_username = username;

	Proxy->Field_password = password;

	Proxy->Field_email = email;


	return Proxy;
}

void Uadmin_session_AdministrationUser_userPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /user put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/user?username=%s&password=%s&email=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_username)

		, *FGenericPlatformHttp::UrlEncode(this->Field_password)

		, *FGenericPlatformHttp::UrlEncode(this->Field_email)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_AdministrationUser_userPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /user put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_AdminUserSummary(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /user put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /user put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_AdministrationUser_userPUT>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_AdministrationUser_verifyPOST::Uadmin_session_AdministrationUser_verifyPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_AdministrationUser_verifyPOST* Uadmin_session_AdministrationUser_verifyPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString username

	, FString code
)
{
	Uadmin_session_AdministrationUser_verifyPOST* Proxy = NewObject<Uadmin_session_AdministrationUser_verifyPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_username = username;

	Proxy->Field_code = code;


	return Proxy;
}

void Uadmin_session_AdministrationUser_verifyPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /verify post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/verify?username=%s&code=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_username)

		, *FGenericPlatformHttp::UrlEncode(this->Field_code)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_AdministrationUser_verifyPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /verify post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /verify post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /verify post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /verify post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /verify post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /verify post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_AdminUserSummary(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /verify post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /verify post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_AdminUserSummary(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_AdministrationUser_verifyPOST>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_projectsGET::Uadmin_session_ProjectInfo_projectsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_projectsGET* Uadmin_session_ProjectInfo_projectsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uadmin_session_ProjectInfo_projectsGET* Proxy = NewObject<Uadmin_session_ProjectInfo_projectsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uadmin_session_ProjectInfo_projectsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /projects get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/projects?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_projectsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /projects get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /projects get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiveadmin_session_Project>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /projects get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /projects get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiveadmin_session_Project>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /projects get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveadmin_session_Project>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /projects get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveadmin_session_Project>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiveadmin_session_Project> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiveadmin_session_Project(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /projects get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /projects get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveadmin_session_Project>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_projectsGET>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_projectGET::Uadmin_session_ProjectInfo_projectGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_projectGET* Uadmin_session_ProjectInfo_projectGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uadmin_session_ProjectInfo_projectGET* Proxy = NewObject<Uadmin_session_ProjectInfo_projectGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uadmin_session_ProjectInfo_projectGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /project get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/project?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_projectGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /project get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_Project(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /project get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_projectGET>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_projectPUT::Uadmin_session_ProjectInfo_projectPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_projectPUT* Uadmin_session_ProjectInfo_projectPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString name
)
{
	Uadmin_session_ProjectInfo_projectPUT* Proxy = NewObject<Uadmin_session_ProjectInfo_projectPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_name = name;


	return Proxy;
}

void Uadmin_session_ProjectInfo_projectPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /project put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/project?name=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_projectPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /project put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_Project(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /project put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_projectPUT>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_projectPOST::Uadmin_session_ProjectInfo_projectPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_projectPOST* Uadmin_session_ProjectInfo_projectPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString name

	, bool active
)
{
	Uadmin_session_ProjectInfo_projectPOST* Proxy = NewObject<Uadmin_session_ProjectInfo_projectPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_name = name;

	Proxy->Field_active = active;


	return Proxy;
}

void Uadmin_session_ProjectInfo_projectPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /project post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/project?id=%s&name=%s&active=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, *FGenericPlatformHttp::UrlEncode(this->Field_active ? TEXT("true") : TEXT("false"))

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_projectPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /project post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveadmin_session_Project(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /project post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /project post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveadmin_session_Project(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_projectPOST>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_accessGET::Uadmin_session_ProjectInfo_accessGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_accessGET* Uadmin_session_ProjectInfo_accessGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uadmin_session_ProjectInfo_accessGET* Proxy = NewObject<Uadmin_session_ProjectInfo_accessGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uadmin_session_ProjectInfo_accessGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /access get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/access?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiveadmin_session_ProjectAccessEntry>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /access get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiveadmin_session_ProjectAccessEntry>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveadmin_session_ProjectAccessEntry>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveadmin_session_ProjectAccessEntry>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiveadmin_session_ProjectAccessEntry> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiveadmin_session_ProjectAccessEntry(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveadmin_session_ProjectAccessEntry>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessGET>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_accessUserPUT::Uadmin_session_ProjectInfo_accessUserPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_accessUserPUT* Uadmin_session_ProjectInfo_accessUserPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString username
)
{
	Uadmin_session_ProjectInfo_accessUserPUT* Proxy = NewObject<Uadmin_session_ProjectInfo_accessUserPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_username = username;


	return Proxy;
}

void Uadmin_session_ProjectInfo_accessUserPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /access/user put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/access/user?id=%s&username=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_username)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessUserPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /access/user put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/user put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/user put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/user put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessUserPUT>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_accessUserDELETE::Uadmin_session_ProjectInfo_accessUserDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_accessUserDELETE* Uadmin_session_ProjectInfo_accessUserDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString username
)
{
	Uadmin_session_ProjectInfo_accessUserDELETE* Proxy = NewObject<Uadmin_session_ProjectInfo_accessUserDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_username = username;


	return Proxy;
}

void Uadmin_session_ProjectInfo_accessUserDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /access/user delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/access/user?id=%s&username=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_username)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessUserDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /access/user delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/user delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/user delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/user delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/user delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessUserDELETE>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_accessProjectPUT::Uadmin_session_ProjectInfo_accessProjectPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_accessProjectPUT* Uadmin_session_ProjectInfo_accessProjectPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString projectId
)
{
	Uadmin_session_ProjectInfo_accessProjectPUT* Proxy = NewObject<Uadmin_session_ProjectInfo_accessProjectPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_projectId = projectId;


	return Proxy;
}

void Uadmin_session_ProjectInfo_accessProjectPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /access/project put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/access/project?id=%s&projectId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_projectId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessProjectPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /access/project put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/project put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/project put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/project put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessProjectPUT>(this));
	HttpRequest->ProcessRequest();
}



Uadmin_session_ProjectInfo_accessProjectDELETE::Uadmin_session_ProjectInfo_accessProjectDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uadmin_session_ProjectInfo_accessProjectDELETE* Uadmin_session_ProjectInfo_accessProjectDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString projectId
)
{
	Uadmin_session_ProjectInfo_accessProjectDELETE* Proxy = NewObject<Uadmin_session_ProjectInfo_accessProjectDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_projectId = projectId;


	return Proxy;
}

void Uadmin_session_ProjectInfo_accessProjectDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] admin-session /access/project delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://admin-session-api.hivemp.com/v1/access/project?id=%s&projectId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_projectId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessProjectDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] admin-session /access/project delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/project delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/project delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] admin-session /access/project delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] admin-session /access/project delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uadmin_session_ProjectInfo_accessProjectDELETE>(this));
	HttpRequest->ProcessRequest();
}



struct FHiveattribute_AttributeKey DeserializeFHiveattribute_AttributeKey(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveattribute_AttributeKey Target;
	

	FString F_key;
	if (obj->TryGetStringField(TEXT("key"), F_key))
	{
		Target.key = F_key;
	}

	FString F_ownerId;
	if (obj->TryGetStringField(TEXT("ownerId"), F_ownerId))
	{
		Target.ownerId = F_ownerId;
	}


	return Target;
}



struct FHiveattribute_AttributeData DeserializeFHiveattribute_AttributeData(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveattribute_AttributeData Target;
	

	FString F_key;
	if (obj->TryGetStringField(TEXT("key"), F_key))
	{
		Target.key = F_key;
	}

	FString F_ownerId;
	if (obj->TryGetStringField(TEXT("ownerId"), F_ownerId))
	{
		Target.ownerId = F_ownerId;
	}

	FString F_value;
	if (obj->TryGetStringField(TEXT("value"), F_value))
	{
		Target.value = F_value;
	}


	return Target;
}



Uattribute_Attribute_attributesGET::Uattribute_Attribute_attributesGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uattribute_Attribute_attributesGET* Uattribute_Attribute_attributesGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uattribute_Attribute_attributesGET* Proxy = NewObject<Uattribute_Attribute_attributesGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uattribute_Attribute_attributesGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] attribute /attributes get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://attribute-api.hivemp.com/v1/attributes?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uattribute_Attribute_attributesGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attributes get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attributes get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiveattribute_AttributeKey>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] attribute /attributes get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attributes get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiveattribute_AttributeKey>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attributes get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveattribute_AttributeKey>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attributes get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveattribute_AttributeKey>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiveattribute_AttributeKey> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiveattribute_AttributeKey(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] attribute /attributes get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attributes get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveattribute_AttributeKey>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uattribute_Attribute_attributesGET>(this));
	HttpRequest->ProcessRequest();
}



Uattribute_Attribute_attributeGET::Uattribute_Attribute_attributeGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uattribute_Attribute_attributeGET* Uattribute_Attribute_attributeGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString key

	, FString ownerId
)
{
	Uattribute_Attribute_attributeGET* Proxy = NewObject<Uattribute_Attribute_attributeGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_key = key;

	Proxy->Field_ownerId = ownerId;


	return Proxy;
}

void Uattribute_Attribute_attributeGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] attribute /attribute get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://attribute-api.hivemp.com/v1/attribute?id=%s&key=%s&ownerId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_key)

		, *FGenericPlatformHttp::UrlEncode(this->Field_ownerId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uattribute_Attribute_attributeGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveattribute_AttributeData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] attribute /attribute get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveattribute_AttributeData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveattribute_AttributeData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveattribute_AttributeData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveattribute_AttributeData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] attribute /attribute get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveattribute_AttributeData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uattribute_Attribute_attributeGET>(this));
	HttpRequest->ProcessRequest();
}



Uattribute_Attribute_attributePUT::Uattribute_Attribute_attributePUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uattribute_Attribute_attributePUT* Uattribute_Attribute_attributePUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString key

	, FString value
)
{
	Uattribute_Attribute_attributePUT* Proxy = NewObject<Uattribute_Attribute_attributePUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_key = key;

	Proxy->Field_value = value;


	return Proxy;
}

void Uattribute_Attribute_attributePUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] attribute /attribute put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://attribute-api.hivemp.com/v1/attribute?id=%s&key=%s&value=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_key)

		, *FGenericPlatformHttp::UrlEncode(this->Field_value)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uattribute_Attribute_attributePUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] attribute /attribute put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] attribute /attribute put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] attribute /attribute put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] attribute /attribute put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uattribute_Attribute_attributePUT>(this));
	HttpRequest->ProcessRequest();
}



Uattribute_Attribute_attributeDELETE::Uattribute_Attribute_attributeDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uattribute_Attribute_attributeDELETE* Uattribute_Attribute_attributeDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString key

	, FString ownerId
)
{
	Uattribute_Attribute_attributeDELETE* Proxy = NewObject<Uattribute_Attribute_attributeDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_key = key;

	Proxy->Field_ownerId = ownerId;


	return Proxy;
}

void Uattribute_Attribute_attributeDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] attribute /attribute delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://attribute-api.hivemp.com/v1/attribute?id=%s&key=%s&ownerId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_key)

		, *FGenericPlatformHttp::UrlEncode(this->Field_ownerId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uattribute_Attribute_attributeDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] attribute /attribute delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] attribute /attribute delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] attribute /attribute delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] attribute /attribute delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] attribute /attribute delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uattribute_Attribute_attributeDELETE>(this));
	HttpRequest->ProcessRequest();
}



struct FHiveevent_EventTypeVersion DeserializeFHiveevent_EventTypeVersion(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveevent_EventTypeVersion Target;
	

	FString F_eventType;
	if (obj->TryGetStringField(TEXT("eventType"), F_eventType))
	{
		Target.eventType = F_eventType;
	}

	FString F_eventTypeVersion;
	if (obj->TryGetStringField(TEXT("eventTypeVersion"), F_eventTypeVersion))
	{
		Target.eventTypeVersion = F_eventTypeVersion;
	}

	FString F_status;
	if (obj->TryGetStringField(TEXT("status"), F_status))
	{
		Target.status = F_status;
	}

	FString F_statusDetailed;
	if (obj->TryGetStringField(TEXT("statusDetailed"), F_statusDetailed))
	{
		Target.statusDetailed = F_statusDetailed;
	}

	FString F_schema;
	if (obj->TryGetStringField(TEXT("schema"), F_schema))
	{
		Target.schema = F_schema;
	}


	return Target;
}



Uevent_Event_eventInsertPUT::Uevent_Event_eventInsertPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uevent_Event_eventInsertPUT* Uevent_Event_eventInsertPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString eventType

	, FString eventTypeVersion

	, FString /* JSON STRING */ event
)
{
	Uevent_Event_eventInsertPUT* Proxy = NewObject<Uevent_Event_eventInsertPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_eventType = eventType;

	Proxy->Field_eventTypeVersion = eventTypeVersion;

	Proxy->Field_event = event;


	return Proxy;
}

void Uevent_Event_eventInsertPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] event /event/insert put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://event-api.hivemp.com/v1/event/insert?eventType=%s&eventTypeVersion=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventType)

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventTypeVersion)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uevent_Event_eventInsertPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] event /event/insert put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /event/insert put: %s"), *(ResultError.Message));
			OnFailure.Broadcast(ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] event /event/insert put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /event/insert put: %s"), *(ResultError.Message));
			OnFailure.Broadcast(ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] event /event/insert put: %s"), *(ResultError.Message));
				OnFailure.Broadcast(ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /event/insert put: %s"), *(ResultError.Message));
				OnFailure.Broadcast(ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			UE_LOG_HIVE(Warning, TEXT("[success] event /event/insert put"));
			OnSuccess.Broadcast(ResultError);
		
		}
	}, TWeakObjectPtr<Uevent_Event_eventInsertPUT>(this));
	HttpRequest->ProcessRequest();
}



Uevent_Event_eventBatchInsertPUT::Uevent_Event_eventBatchInsertPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uevent_Event_eventBatchInsertPUT* Uevent_Event_eventBatchInsertPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString eventType

	, FString eventTypeVersion

	, FString /* JSON STRING */ events
)
{
	Uevent_Event_eventBatchInsertPUT* Proxy = NewObject<Uevent_Event_eventBatchInsertPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_eventType = eventType;

	Proxy->Field_eventTypeVersion = eventTypeVersion;

	Proxy->Field_events = events;


	return Proxy;
}

void Uevent_Event_eventBatchInsertPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] event /event/batchInsert put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://event-api.hivemp.com/v1/event/batchInsert?eventType=%s&eventTypeVersion=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventType)

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventTypeVersion)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uevent_Event_eventBatchInsertPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] event /event/batchInsert put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /event/batchInsert put: %s"), *(ResultError.Message));
			OnFailure.Broadcast(ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] event /event/batchInsert put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /event/batchInsert put: %s"), *(ResultError.Message));
			OnFailure.Broadcast(ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] event /event/batchInsert put: %s"), *(ResultError.Message));
				OnFailure.Broadcast(ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /event/batchInsert put: %s"), *(ResultError.Message));
				OnFailure.Broadcast(ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			UE_LOG_HIVE(Warning, TEXT("[success] event /event/batchInsert put"));
			OnSuccess.Broadcast(ResultError);
		
		}
	}, TWeakObjectPtr<Uevent_Event_eventBatchInsertPUT>(this));
	HttpRequest->ProcessRequest();
}



Uevent_EventTypes_typesGET::Uevent_EventTypes_typesGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uevent_EventTypes_typesGET* Uevent_EventTypes_typesGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit
)
{
	Uevent_EventTypes_typesGET* Proxy = NewObject<Uevent_EventTypes_typesGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;


	return Proxy;
}

void Uevent_EventTypes_typesGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] event /types get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://event-api.hivemp.com/v1/types?start=%s&limit=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uevent_EventTypes_typesGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] event /types get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /types get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiveevent_EventTypeVersion>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] event /types get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /types get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiveevent_EventTypeVersion>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] event /types get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveevent_EventTypeVersion>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /types get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveevent_EventTypeVersion>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiveevent_EventTypeVersion> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiveevent_EventTypeVersion(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] event /types get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /types get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiveevent_EventTypeVersion>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uevent_EventTypes_typesGET>(this));
	HttpRequest->ProcessRequest();
}



Uevent_EventTypes_typeGET::Uevent_EventTypes_typeGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uevent_EventTypes_typeGET* Uevent_EventTypes_typeGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString eventType

	, FString eventTypeVersion
)
{
	Uevent_EventTypes_typeGET* Proxy = NewObject<Uevent_EventTypes_typeGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_eventType = eventType;

	Proxy->Field_eventTypeVersion = eventTypeVersion;


	return Proxy;
}

void Uevent_EventTypes_typeGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] event /type get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://event-api.hivemp.com/v1/type?eventType=%s&eventTypeVersion=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventType)

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventTypeVersion)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uevent_EventTypes_typeGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] event /type get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /type get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] event /type get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /type get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] event /type get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /type get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveevent_EventTypeVersion(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] event /type get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /type get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uevent_EventTypes_typeGET>(this));
	HttpRequest->ProcessRequest();
}



Uevent_EventTypes_typePUT::Uevent_EventTypes_typePUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uevent_EventTypes_typePUT* Uevent_EventTypes_typePUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString eventType

	, FString schema
)
{
	Uevent_EventTypes_typePUT* Proxy = NewObject<Uevent_EventTypes_typePUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_eventType = eventType;

	Proxy->Field_schema = schema;


	return Proxy;
}

void Uevent_EventTypes_typePUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] event /type put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://event-api.hivemp.com/v1/type?eventType=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventType)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uevent_EventTypes_typePUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] event /type put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /type put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] event /type put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /type put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] event /type put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /type put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveevent_EventTypeVersion(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] event /type put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /type put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uevent_EventTypes_typePUT>(this));
	HttpRequest->ProcessRequest();
}



Uevent_EventTypes_typePOST::Uevent_EventTypes_typePOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uevent_EventTypes_typePOST* Uevent_EventTypes_typePOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString eventType

	, FString eventTypeVersion

	, FString schema
)
{
	Uevent_EventTypes_typePOST* Proxy = NewObject<Uevent_EventTypes_typePOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_eventType = eventType;

	Proxy->Field_eventTypeVersion = eventTypeVersion;

	Proxy->Field_schema = schema;


	return Proxy;
}

void Uevent_EventTypes_typePOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] event /type post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://event-api.hivemp.com/v1/type?eventType=%s&eventTypeVersion=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventType)

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventTypeVersion)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uevent_EventTypes_typePOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] event /type post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /type post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] event /type post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /type post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] event /type post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /type post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveevent_EventTypeVersion(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] event /type post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /type post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uevent_EventTypes_typePOST>(this));
	HttpRequest->ProcessRequest();
}



Uevent_EventTypes_typeDELETE::Uevent_EventTypes_typeDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uevent_EventTypes_typeDELETE* Uevent_EventTypes_typeDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString eventType

	, FString eventTypeVersion
)
{
	Uevent_EventTypes_typeDELETE* Proxy = NewObject<Uevent_EventTypes_typeDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_eventType = eventType;

	Proxy->Field_eventTypeVersion = eventTypeVersion;


	return Proxy;
}

void Uevent_EventTypes_typeDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] event /type delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://event-api.hivemp.com/v1/type?eventType=%s&eventTypeVersion=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventType)

		, *FGenericPlatformHttp::UrlEncode(this->Field_eventTypeVersion)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uevent_EventTypes_typeDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] event /type delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /type delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] event /type delete: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] event /type delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] event /type delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /type delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveevent_EventTypeVersion(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] event /type delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] event /type delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveevent_EventTypeVersion(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uevent_EventTypes_typeDELETE>(this));
	HttpRequest->ProcessRequest();
}



struct FHivegame_server_PaginatedGameServers DeserializeFHivegame_server_PaginatedGameServers(const TSharedPtr<FJsonObject> obj)
{
	struct FHivegame_server_PaginatedGameServers Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHivegame_server_GameServer(*A_results));
			}

		}
	}


	return Target;
}



struct FHivegame_server_GameServer DeserializeFHivegame_server_GameServer(const TSharedPtr<FJsonObject> obj)
{
	struct FHivegame_server_GameServer Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_templateId;
	if (obj->TryGetStringField(TEXT("templateId"), F_templateId))
	{
		Target.templateId = F_templateId;
	}

	FString F_version;
	if (obj->TryGetStringField(TEXT("version"), F_version))
	{
		Target.version = F_version;
	}

	double F_billedSliceMinutes;
	if (obj->TryGetNumberField(TEXT("billedSliceMinutes"), F_billedSliceMinutes))
	{
		Target.billedSliceMinutes = (int32)F_billedSliceMinutes;
	}

	double F_slices;
	if (obj->TryGetNumberField(TEXT("slices"), F_slices))
	{
		Target.slices = (int32)F_slices;
	}

	FString F_status;
	if (obj->TryGetStringField(TEXT("status"), F_status))
	{
		Target.status = F_status;
	}

	double F_start;
	if (obj->TryGetNumberField(TEXT("start"), F_start))
	{
		Target.start = (int32)F_start;
	}

	FString F_serverIpAddress;
	if (obj->TryGetStringField(TEXT("serverIpAddress"), F_serverIpAddress))
	{
		Target.serverIpAddress = F_serverIpAddress;
	}

	double F_serverPort;
	if (obj->TryGetNumberField(TEXT("serverPort"), F_serverPort))
	{
		Target.serverPort = (int32)F_serverPort;
	}

	double F_billingStart;
	if (obj->TryGetNumberField(TEXT("billingStart"), F_billingStart))
	{
		Target.billingStart = (int32)F_billingStart;
	}

	double F_billingEnd;
	if (obj->TryGetNumberField(TEXT("billingEnd"), F_billingEnd))
	{
		Target.billingEnd = (int32)F_billingEnd;
	}

	double F_expiry;
	if (obj->TryGetNumberField(TEXT("expiry"), F_expiry))
	{
		Target.expiry = (int32)F_expiry;
	}


	return Target;
}



struct FHivegame_server_GameServerTemplate DeserializeFHivegame_server_GameServerTemplate(const TSharedPtr<FJsonObject> obj)
{
	struct FHivegame_server_GameServerTemplate Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_dockerImageName;
	if (obj->TryGetStringField(TEXT("dockerImageName"), F_dockerImageName))
	{
		Target.dockerImageName = F_dockerImageName;
	}

	FString F_gcrServiceAccountJson;
	if (obj->TryGetStringField(TEXT("gcrServiceAccountJson"), F_gcrServiceAccountJson))
	{
		Target.gcrServiceAccountJson = F_gcrServiceAccountJson;
	}

	FString F_containerHostPlatform;
	if (obj->TryGetStringField(TEXT("containerHostPlatform"), F_containerHostPlatform))
	{
		Target.containerHostPlatform = F_containerHostPlatform;
	}

	double F_slices;
	if (obj->TryGetNumberField(TEXT("slices"), F_slices))
	{
		Target.slices = (int32)F_slices;
	}


	return Target;
}



Ugame_server_GameServer_serversGET::Ugame_server_GameServer_serversGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServer_serversGET* Ugame_server_GameServer_serversGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit
)
{
	Ugame_server_GameServer_serversGET* Proxy = NewObject<Ugame_server_GameServer_serversGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;


	return Proxy;
}

void Ugame_server_GameServer_serversGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /servers get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/servers?start=%s&limit=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServer_serversGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /servers get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /servers get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_PaginatedGameServers(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /servers get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /servers get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_PaginatedGameServers(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /servers get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_PaginatedGameServers(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /servers get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_PaginatedGameServers(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivegame_server_PaginatedGameServers(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /servers get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /servers get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_PaginatedGameServers(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServer_serversGET>(this));
	HttpRequest->ProcessRequest();
}



Ugame_server_GameServer_serverGET::Ugame_server_GameServer_serverGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServer_serverGET* Ugame_server_GameServer_serverGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Ugame_server_GameServer_serverGET* Proxy = NewObject<Ugame_server_GameServer_serverGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Ugame_server_GameServer_serverGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /server get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/server?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServer_serverGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /server get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivegame_server_GameServer(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /server get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServer_serverGET>(this));
	HttpRequest->ProcessRequest();
}



Ugame_server_GameServer_serverStatusPOST::Ugame_server_GameServer_serverStatusPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServer_serverStatusPOST* Ugame_server_GameServer_serverStatusPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString status

	, FString address

	, int32 port

	, int32 billingStart

	, int32 billingEnd
)
{
	Ugame_server_GameServer_serverStatusPOST* Proxy = NewObject<Ugame_server_GameServer_serverStatusPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_status = status;

	Proxy->Field_address = address;

	Proxy->Field_port = port;

	Proxy->Field_billingStart = billingStart;

	Proxy->Field_billingEnd = billingEnd;


	return Proxy;
}

void Ugame_server_GameServer_serverStatusPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /server/status post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/server/status?id=%s&status=%s&address=%s&port=%i&billingStart=%i&billingEnd=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_status)

		, *FGenericPlatformHttp::UrlEncode(this->Field_address)

		, this->Field_port

		, this->Field_billingStart

		, this->Field_billingEnd

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServer_serverStatusPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/status post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/status post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /server/status post: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] game-server /server/status post"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] game-server /server/status post"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/status post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/status post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/status post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /server/status post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/status post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServer_serverStatusPOST>(this));
	HttpRequest->ProcessRequest();
}



Ugame_server_GameServer_serverCleanupPOST::Ugame_server_GameServer_serverCleanupPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServer_serverCleanupPOST* Ugame_server_GameServer_serverCleanupPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, int32 billingStart

	, int32 billingEnd
)
{
	Ugame_server_GameServer_serverCleanupPOST* Proxy = NewObject<Ugame_server_GameServer_serverCleanupPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_billingStart = billingStart;

	Proxy->Field_billingEnd = billingEnd;


	return Proxy;
}

void Ugame_server_GameServer_serverCleanupPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /server/cleanup post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/server/cleanup?id=%s&billingStart=%i&billingEnd=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, this->Field_billingStart

		, this->Field_billingEnd

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServer_serverCleanupPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/cleanup post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/cleanup post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /server/cleanup post: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] game-server /server/cleanup post"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] game-server /server/cleanup post"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/cleanup post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/cleanup post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/cleanup post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /server/cleanup post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /server/cleanup post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServer_serverCleanupPOST>(this));
	HttpRequest->ProcessRequest();
}



Ugame_server_GameServer_provisionPUT::Ugame_server_GameServer_provisionPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServer_provisionPUT* Ugame_server_GameServer_provisionPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString templateId

	, FString version
)
{
	Ugame_server_GameServer_provisionPUT* Proxy = NewObject<Ugame_server_GameServer_provisionPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_templateId = templateId;

	Proxy->Field_version = version;


	return Proxy;
}

void Ugame_server_GameServer_provisionPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /provision put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/provision?templateId=%s&version=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_templateId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_version)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServer_provisionPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /provision put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /provision put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /provision put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /provision put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /provision put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /provision put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivegame_server_GameServer(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /provision put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /provision put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServer(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServer_provisionPUT>(this));
	HttpRequest->ProcessRequest();
}



Ugame_server_GameServerTemplate_templateGET::Ugame_server_GameServerTemplate_templateGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServerTemplate_templateGET* Ugame_server_GameServerTemplate_templateGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Ugame_server_GameServerTemplate_templateGET* Proxy = NewObject<Ugame_server_GameServerTemplate_templateGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Ugame_server_GameServerTemplate_templateGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /template get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/template?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServerTemplate_templateGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /template get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivegame_server_GameServerTemplate(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /template get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServerTemplate_templateGET>(this));
	HttpRequest->ProcessRequest();
}



Ugame_server_GameServerTemplate_templatePUT::Ugame_server_GameServerTemplate_templatePUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServerTemplate_templatePUT* Ugame_server_GameServerTemplate_templatePUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString dockerImageName

	, FString gcrServiceAccountJson

	, FString containerHostPlatform

	, int32 slices
)
{
	Ugame_server_GameServerTemplate_templatePUT* Proxy = NewObject<Ugame_server_GameServerTemplate_templatePUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_dockerImageName = dockerImageName;

	Proxy->Field_gcrServiceAccountJson = gcrServiceAccountJson;

	Proxy->Field_containerHostPlatform = containerHostPlatform;

	Proxy->Field_slices = slices;


	return Proxy;
}

void Ugame_server_GameServerTemplate_templatePUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /template put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/template?id=%s&dockerImageName=%s&gcrServiceAccountJson=%s&containerHostPlatform=%s&slices=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_dockerImageName)

		, *FGenericPlatformHttp::UrlEncode(this->Field_gcrServiceAccountJson)

		, *FGenericPlatformHttp::UrlEncode(this->Field_containerHostPlatform)

		, this->Field_slices

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServerTemplate_templatePUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /template put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivegame_server_GameServerTemplate(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /template put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServerTemplate_templatePUT>(this));
	HttpRequest->ProcessRequest();
}



Ugame_server_GameServerTemplate_templatePOST::Ugame_server_GameServerTemplate_templatePOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServerTemplate_templatePOST* Ugame_server_GameServerTemplate_templatePOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString dockerImageName

	, FString gcrServiceAccountJson

	, FString containerHostPlatform

	, int32 slices
)
{
	Ugame_server_GameServerTemplate_templatePOST* Proxy = NewObject<Ugame_server_GameServerTemplate_templatePOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_dockerImageName = dockerImageName;

	Proxy->Field_gcrServiceAccountJson = gcrServiceAccountJson;

	Proxy->Field_containerHostPlatform = containerHostPlatform;

	Proxy->Field_slices = slices;


	return Proxy;
}

void Ugame_server_GameServerTemplate_templatePOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /template post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/template?id=%s&dockerImageName=%s&gcrServiceAccountJson=%s&containerHostPlatform=%s&slices=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_dockerImageName)

		, *FGenericPlatformHttp::UrlEncode(this->Field_gcrServiceAccountJson)

		, *FGenericPlatformHttp::UrlEncode(this->Field_containerHostPlatform)

		, this->Field_slices

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServerTemplate_templatePOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /template post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivegame_server_GameServerTemplate(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /template post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivegame_server_GameServerTemplate(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServerTemplate_templatePOST>(this));
	HttpRequest->ProcessRequest();
}



Ugame_server_GameServerTemplate_templateDELETE::Ugame_server_GameServerTemplate_templateDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ugame_server_GameServerTemplate_templateDELETE* Ugame_server_GameServerTemplate_templateDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Ugame_server_GameServerTemplate_templateDELETE* Proxy = NewObject<Ugame_server_GameServerTemplate_templateDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Ugame_server_GameServerTemplate_templateDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] game-server /template delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://game-server-api.hivemp.com/v1/template?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ugame_server_GameServerTemplate_templateDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] game-server /template delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] game-server /template delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] game-server /template delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] game-server /template delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] game-server /template delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] game-server /template delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ugame_server_GameServerTemplate_templateDELETE>(this));
	HttpRequest->ProcessRequest();
}



struct FHiveintegration_SteamIntegrationSummary DeserializeFHiveintegration_SteamIntegrationSummary(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveintegration_SteamIntegrationSummary Target;
	

	FString F_appId;
	if (obj->TryGetStringField(TEXT("appId"), F_appId))
	{
		Target.appId = F_appId;
	}

	FString F_partnerPortalUsername;
	if (obj->TryGetStringField(TEXT("partnerPortalUsername"), F_partnerPortalUsername))
	{
		Target.partnerPortalUsername = F_partnerPortalUsername;
	}

	FString F_connectionStatus;
	if (obj->TryGetStringField(TEXT("connectionStatus"), F_connectionStatus))
	{
		Target.connectionStatus = F_connectionStatus;
	}

	FString F_lastAuthError;
	if (obj->TryGetStringField(TEXT("lastAuthError"), F_lastAuthError))
	{
		Target.lastAuthError = F_lastAuthError;
	}

	double F_lastRecordedWishlistDate;
	if (obj->TryGetNumberField(TEXT("lastRecordedWishlistDate"), F_lastRecordedWishlistDate))
	{
		Target.lastRecordedWishlistDate = (int32)F_lastRecordedWishlistDate;
	}

	double F_lastRecordedTrafficDate;
	if (obj->TryGetNumberField(TEXT("lastRecordedTrafficDate"), F_lastRecordedTrafficDate))
	{
		Target.lastRecordedTrafficDate = (int32)F_lastRecordedTrafficDate;
	}

	double F_lastRecordedSalesDate;
	if (obj->TryGetNumberField(TEXT("lastRecordedSalesDate"), F_lastRecordedSalesDate))
	{
		Target.lastRecordedSalesDate = (int32)F_lastRecordedSalesDate;
	}


	return Target;
}



struct FHiveintegration_SteamGuardStatus DeserializeFHiveintegration_SteamGuardStatus(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveintegration_SteamGuardStatus Target;
	

	FString F_status;
	if (obj->TryGetStringField(TEXT("status"), F_status))
	{
		Target.status = F_status;
	}


	return Target;
}



struct FHiveintegration_SteamCredentials DeserializeFHiveintegration_SteamCredentials(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveintegration_SteamCredentials Target;
	

	FString F_encryptedAppId;
	if (obj->TryGetStringField(TEXT("encryptedAppId"), F_encryptedAppId))
	{
		Target.encryptedAppId = F_encryptedAppId;
	}

	FString F_encryptedPublisherKey;
	if (obj->TryGetStringField(TEXT("encryptedPublisherKey"), F_encryptedPublisherKey))
	{
		Target.encryptedPublisherKey = F_encryptedPublisherKey;
	}

	FString F_encryptedPublisherUsername;
	if (obj->TryGetStringField(TEXT("encryptedPublisherUsername"), F_encryptedPublisherUsername))
	{
		Target.encryptedPublisherUsername = F_encryptedPublisherUsername;
	}

	FString F_encryptedPublisherPassword;
	if (obj->TryGetStringField(TEXT("encryptedPublisherPassword"), F_encryptedPublisherPassword))
	{
		Target.encryptedPublisherPassword = F_encryptedPublisherPassword;
	}

	FString F_encryptedPartnerSteamGuardCookie;
	if (obj->TryGetStringField(TEXT("encryptedPartnerSteamGuardCookie"), F_encryptedPartnerSteamGuardCookie))
	{
		Target.encryptedPartnerSteamGuardCookie = F_encryptedPartnerSteamGuardCookie;
	}

	FString F_encryptedPartnerCurrentPoweredCookie;
	if (obj->TryGetStringField(TEXT("encryptedPartnerCurrentPoweredCookie"), F_encryptedPartnerCurrentPoweredCookie))
	{
		Target.encryptedPartnerCurrentPoweredCookie = F_encryptedPartnerCurrentPoweredCookie;
	}

	FString F_encryptedPartnerCurrentGamesCookie;
	if (obj->TryGetStringField(TEXT("encryptedPartnerCurrentGamesCookie"), F_encryptedPartnerCurrentGamesCookie))
	{
		Target.encryptedPartnerCurrentGamesCookie = F_encryptedPartnerCurrentGamesCookie;
	}

	FString F_encryptedPartnerCurrentGamesSessionCookie;
	if (obj->TryGetStringField(TEXT("encryptedPartnerCurrentGamesSessionCookie"), F_encryptedPartnerCurrentGamesSessionCookie))
	{
		Target.encryptedPartnerCurrentGamesSessionCookie = F_encryptedPartnerCurrentGamesSessionCookie;
	}


	return Target;
}



struct FHiveintegration_SteamSaleDataState DeserializeFHiveintegration_SteamSaleDataState(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveintegration_SteamSaleDataState Target;
	

	double F_date;
	if (obj->TryGetNumberField(TEXT("date"), F_date))
	{
		Target.date = (int32)F_date;
	}

	double F_index;
	if (obj->TryGetNumberField(TEXT("index"), F_index))
	{
		Target.index = (int32)F_index;
	}


	return Target;
}



Uintegration_Steam_steamPUT::Uintegration_Steam_steamPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamPUT* Uintegration_Steam_steamPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString steamAppId

	, FString publisherKey

	, FString publisherUsername

	, FString publisherPassword
)
{
	Uintegration_Steam_steamPUT* Proxy = NewObject<Uintegration_Steam_steamPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_steamAppId = steamAppId;

	Proxy->Field_publisherKey = publisherKey;

	Proxy->Field_publisherUsername = publisherUsername;

	Proxy->Field_publisherPassword = publisherPassword;


	return Proxy;
}

void Uintegration_Steam_steamPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam?steamAppId=%s&publisherKey=%s&publisherUsername=%s&publisherPassword=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_steamAppId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_publisherKey)

		, *FGenericPlatformHttp::UrlEncode(this->Field_publisherUsername)

		, *FGenericPlatformHttp::UrlEncode(this->Field_publisherPassword)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamStatusGET::Uintegration_Steam_steamStatusGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamStatusGET* Uintegration_Steam_steamStatusGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_Steam_steamStatusGET* Proxy = NewObject<Uintegration_Steam_steamStatusGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_Steam_steamStatusGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/status get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/status?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamStatusGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/status get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/status get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveintegration_SteamIntegrationSummary(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/status get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/status get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveintegration_SteamIntegrationSummary(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/status get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamIntegrationSummary(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/status get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamIntegrationSummary(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveintegration_SteamIntegrationSummary(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/status get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/status get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamIntegrationSummary(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamStatusGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamGuardGET::Uintegration_Steam_steamGuardGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamGuardGET* Uintegration_Steam_steamGuardGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_Steam_steamGuardGET* Proxy = NewObject<Uintegration_Steam_steamGuardGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_Steam_steamGuardGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/guard get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/guard?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamGuardGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveintegration_SteamGuardStatus(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/guard get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveintegration_SteamGuardStatus(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamGuardStatus(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamGuardStatus(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveintegration_SteamGuardStatus(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/guard get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamGuardStatus(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamGuardGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamGuardPUT::Uintegration_Steam_steamGuardPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamGuardPUT* Uintegration_Steam_steamGuardPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString steamGuardCode
)
{
	Uintegration_Steam_steamGuardPUT* Proxy = NewObject<Uintegration_Steam_steamGuardPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_steamGuardCode = steamGuardCode;


	return Proxy;
}

void Uintegration_Steam_steamGuardPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/guard put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/guard?steamGuardCode=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_steamGuardCode)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamGuardPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/guard put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/guard put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/guard put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/guard put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamGuardPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamReimportPUT::Uintegration_Steam_steamReimportPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamReimportPUT* Uintegration_Steam_steamReimportPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_Steam_steamReimportPUT* Proxy = NewObject<Uintegration_Steam_steamReimportPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_Steam_steamReimportPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/reimport put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/reimport?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamReimportPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/reimport put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/reimport put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/reimport put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/reimport put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/reimport put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/reimport put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/reimport put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/reimport put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/reimport put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/reimport put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamReimportPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamCredentialsGET::Uintegration_Steam_steamCredentialsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamCredentialsGET* Uintegration_Steam_steamCredentialsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_Steam_steamCredentialsGET* Proxy = NewObject<Uintegration_Steam_steamCredentialsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_Steam_steamCredentialsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/credentials get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/credentials?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamCredentialsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveintegration_SteamCredentials(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/credentials get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveintegration_SteamCredentials(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamCredentials(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamCredentials(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveintegration_SteamCredentials(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamCredentials(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamCredentialsGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamConfiguredGET::Uintegration_Steam_steamConfiguredGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamConfiguredGET* Uintegration_Steam_steamConfiguredGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_Steam_steamConfiguredGET* Proxy = NewObject<Uintegration_Steam_steamConfiguredGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_Steam_steamConfiguredGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/configured get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/configured?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamConfiguredGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/configured get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/configured get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/configured get: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/configured get"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/configured get"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/configured get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/configured get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/configured get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/configured get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/configured get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamConfiguredGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamCredentialsGamesPUT::Uintegration_Steam_steamCredentialsGamesPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamCredentialsGamesPUT* Uintegration_Steam_steamCredentialsGamesPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString encryptedGamesCookie

	, FString encryptedSessionCookie
)
{
	Uintegration_Steam_steamCredentialsGamesPUT* Proxy = NewObject<Uintegration_Steam_steamCredentialsGamesPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_encryptedGamesCookie = encryptedGamesCookie;

	Proxy->Field_encryptedSessionCookie = encryptedSessionCookie;


	return Proxy;
}

void Uintegration_Steam_steamCredentialsGamesPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/credentials/games put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/credentials/games?encryptedGamesCookie=%s&encryptedSessionCookie=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_encryptedGamesCookie)

		, *FGenericPlatformHttp::UrlEncode(this->Field_encryptedSessionCookie)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamCredentialsGamesPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/games put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/games put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/credentials/games put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/games put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/games put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/games put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/games put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/games put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/games put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/games put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamCredentialsGamesPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamCredentialsPoweredPUT::Uintegration_Steam_steamCredentialsPoweredPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamCredentialsPoweredPUT* Uintegration_Steam_steamCredentialsPoweredPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString encryptedPoweredCookie
)
{
	Uintegration_Steam_steamCredentialsPoweredPUT* Proxy = NewObject<Uintegration_Steam_steamCredentialsPoweredPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_encryptedPoweredCookie = encryptedPoweredCookie;


	return Proxy;
}

void Uintegration_Steam_steamCredentialsPoweredPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/credentials/powered put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/credentials/powered?encryptedPoweredCookie=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_encryptedPoweredCookie)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamCredentialsPoweredPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/powered put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/powered put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/credentials/powered put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/powered put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/powered put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/powered put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/powered put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/powered put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/powered put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/powered put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamCredentialsPoweredPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamCredentialsGuardPUT::Uintegration_Steam_steamCredentialsGuardPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamCredentialsGuardPUT* Uintegration_Steam_steamCredentialsGuardPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString encryptedGuardCookie

	, FString steamGuardStatus
)
{
	Uintegration_Steam_steamCredentialsGuardPUT* Proxy = NewObject<Uintegration_Steam_steamCredentialsGuardPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_encryptedGuardCookie = encryptedGuardCookie;

	Proxy->Field_steamGuardStatus = steamGuardStatus;


	return Proxy;
}

void Uintegration_Steam_steamCredentialsGuardPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/credentials/guard put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/credentials/guard?encryptedGuardCookie=%s&steamGuardStatus=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_encryptedGuardCookie)

		, *FGenericPlatformHttp::UrlEncode(this->Field_steamGuardStatus)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamCredentialsGuardPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/guard put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/guard put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/credentials/guard put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/guard put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/guard put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/guard put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/guard put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/guard put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/credentials/guard put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/credentials/guard put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamCredentialsGuardPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamGuardStatusPUT::Uintegration_Steam_steamGuardStatusPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamGuardStatusPUT* Uintegration_Steam_steamGuardStatusPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString steamGuardStatus
)
{
	Uintegration_Steam_steamGuardStatusPUT* Proxy = NewObject<Uintegration_Steam_steamGuardStatusPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_steamGuardStatus = steamGuardStatus;


	return Proxy;
}

void Uintegration_Steam_steamGuardStatusPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/guard/status put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/guard/status?steamGuardStatus=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_steamGuardStatus)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamGuardStatusPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard/status put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard/status put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/guard/status put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/guard/status put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/guard/status put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard/status put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard/status put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard/status put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/guard/status put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/guard/status put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamGuardStatusPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamErrormsgGET::Uintegration_Steam_steamErrormsgGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamErrormsgGET* Uintegration_Steam_steamErrormsgGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_Steam_steamErrormsgGET* Proxy = NewObject<Uintegration_Steam_steamErrormsgGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_Steam_steamErrormsgGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/errormsg get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/errormsg?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamErrormsgGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TEXT(""), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/errormsg get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TEXT(""), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TEXT(""), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TEXT(""), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			FString Result;
			if (JsonValue->TryGetString(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/errormsg get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TEXT(""), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamErrormsgGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamErrormsgPUT::Uintegration_Steam_steamErrormsgPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamErrormsgPUT* Uintegration_Steam_steamErrormsgPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString message
)
{
	Uintegration_Steam_steamErrormsgPUT* Proxy = NewObject<Uintegration_Steam_steamErrormsgPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_message = message;


	return Proxy;
}

void Uintegration_Steam_steamErrormsgPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/errormsg put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/errormsg?message=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_message)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamErrormsgPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/errormsg put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/errormsg put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/errormsg put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/errormsg put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/errormsg put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamErrormsgPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamEmailidGET::Uintegration_Steam_steamEmailidGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamEmailidGET* Uintegration_Steam_steamEmailidGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_Steam_steamEmailidGET* Proxy = NewObject<Uintegration_Steam_steamEmailidGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_Steam_steamEmailidGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/emailid get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/emailid?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamEmailidGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TEXT(""), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/emailid get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TEXT(""), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TEXT(""), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TEXT(""), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			FString Result;
			if (JsonValue->TryGetString(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/emailid get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TEXT(""), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamEmailidGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_Steam_steamEmailidPUT::Uintegration_Steam_steamEmailidPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_Steam_steamEmailidPUT* Uintegration_Steam_steamEmailidPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString emailId
)
{
	Uintegration_Steam_steamEmailidPUT* Proxy = NewObject<Uintegration_Steam_steamEmailidPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_emailId = emailId;


	return Proxy;
}

void Uintegration_Steam_steamEmailidPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/emailid put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/emailid?emailId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_emailId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_Steam_steamEmailidPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/emailid put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/emailid put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/emailid put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/emailid put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/emailid put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_Steam_steamEmailidPUT>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_SteamState_steamStateWishlistGET::Uintegration_SteamState_steamStateWishlistGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_SteamState_steamStateWishlistGET* Uintegration_SteamState_steamStateWishlistGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_SteamState_steamStateWishlistGET* Proxy = NewObject<Uintegration_SteamState_steamStateWishlistGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_SteamState_steamStateWishlistGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/state/wishlist get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/state/wishlist?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_SteamState_steamStateWishlistGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/state/wishlist get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			double Result;
			if (JsonValue->TryGetNumber(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/wishlist get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_SteamState_steamStateWishlistGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_SteamState_steamStateWishlistPOST::Uintegration_SteamState_steamStateWishlistPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_SteamState_steamStateWishlistPOST* Uintegration_SteamState_steamStateWishlistPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 wishlistDataDate
)
{
	Uintegration_SteamState_steamStateWishlistPOST* Proxy = NewObject<Uintegration_SteamState_steamStateWishlistPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_wishlistDataDate = wishlistDataDate;


	return Proxy;
}

void Uintegration_SteamState_steamStateWishlistPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/state/wishlist post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/state/wishlist?wishlistDataDate=%i")

		, this->Field_wishlistDataDate

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_SteamState_steamStateWishlistPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/state/wishlist post: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/wishlist post"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/wishlist post"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/wishlist post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/wishlist post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_SteamState_steamStateWishlistPOST>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_SteamState_steamStateSalesGET::Uintegration_SteamState_steamStateSalesGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_SteamState_steamStateSalesGET* Uintegration_SteamState_steamStateSalesGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_SteamState_steamStateSalesGET* Proxy = NewObject<Uintegration_SteamState_steamStateSalesGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_SteamState_steamStateSalesGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/state/sales get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/state/sales?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_SteamState_steamStateSalesGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveintegration_SteamSaleDataState(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/state/sales get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveintegration_SteamSaleDataState(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamSaleDataState(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamSaleDataState(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveintegration_SteamSaleDataState(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/sales get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveintegration_SteamSaleDataState(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_SteamState_steamStateSalesGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_SteamState_steamStateSalesPOST::Uintegration_SteamState_steamStateSalesPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_SteamState_steamStateSalesPOST* Uintegration_SteamState_steamStateSalesPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 salesDataDate

	, int32 salesDataIndex
)
{
	Uintegration_SteamState_steamStateSalesPOST* Proxy = NewObject<Uintegration_SteamState_steamStateSalesPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_salesDataDate = salesDataDate;

	Proxy->Field_salesDataIndex = salesDataIndex;


	return Proxy;
}

void Uintegration_SteamState_steamStateSalesPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/state/sales post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/state/sales?salesDataDate=%i&salesDataIndex=%i")

		, this->Field_salesDataDate

		, this->Field_salesDataIndex

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_SteamState_steamStateSalesPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/state/sales post: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/sales post"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/sales post"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/sales post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/sales post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_SteamState_steamStateSalesPOST>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_SteamState_steamStateTrafficGET::Uintegration_SteamState_steamStateTrafficGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_SteamState_steamStateTrafficGET* Uintegration_SteamState_steamStateTrafficGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Uintegration_SteamState_steamStateTrafficGET* Proxy = NewObject<Uintegration_SteamState_steamStateTrafficGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Uintegration_SteamState_steamStateTrafficGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/state/traffic get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/state/traffic?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_SteamState_steamStateTrafficGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/state/traffic get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			double Result;
			if (JsonValue->TryGetNumber(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/traffic get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_SteamState_steamStateTrafficGET>(this));
	HttpRequest->ProcessRequest();
}



Uintegration_SteamState_steamStateTrafficPOST::Uintegration_SteamState_steamStateTrafficPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uintegration_SteamState_steamStateTrafficPOST* Uintegration_SteamState_steamStateTrafficPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 trafficDataDate
)
{
	Uintegration_SteamState_steamStateTrafficPOST* Proxy = NewObject<Uintegration_SteamState_steamStateTrafficPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_trafficDataDate = trafficDataDate;


	return Proxy;
}

void Uintegration_SteamState_steamStateTrafficPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] integration /steam/state/traffic post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://integration-api.hivemp.com/v1/steam/state/traffic?trafficDataDate=%i")

		, this->Field_trafficDataDate

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uintegration_SteamState_steamStateTrafficPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] integration /steam/state/traffic post: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/traffic post"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/traffic post"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] integration /steam/state/traffic post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] integration /steam/state/traffic post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uintegration_SteamState_steamStateTrafficPOST>(this));
	HttpRequest->ProcessRequest();
}



struct FHivelobby_PaginatedGameLobbies DeserializeFHivelobby_PaginatedGameLobbies(const TSharedPtr<FJsonObject> obj)
{
	struct FHivelobby_PaginatedGameLobbies Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHivelobby_LobbyInfo(*A_results));
			}

		}
	}


	return Target;
}



struct FHivelobby_LobbyInfo DeserializeFHivelobby_LobbyInfo(const TSharedPtr<FJsonObject> obj)
{
	struct FHivelobby_LobbyInfo Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_name;
	if (obj->TryGetStringField(TEXT("name"), F_name))
	{
		Target.name = F_name;
	}

	FString F_ownerSessionId;
	if (obj->TryGetStringField(TEXT("ownerSessionId"), F_ownerSessionId))
	{
		Target.ownerSessionId = F_ownerSessionId;
	}

	double F_currentSessions;
	if (obj->TryGetNumberField(TEXT("currentSessions"), F_currentSessions))
	{
		Target.currentSessions = (int32)F_currentSessions;
	}

	double F_maxSessions;
	if (obj->TryGetNumberField(TEXT("maxSessions"), F_maxSessions))
	{
		Target.maxSessions = (int32)F_maxSessions;
	}


	return Target;
}



struct FHivelobby_ConnectedSession DeserializeFHivelobby_ConnectedSession(const TSharedPtr<FJsonObject> obj)
{
	struct FHivelobby_ConnectedSession Target;
	

	FString F_lobbyId;
	if (obj->TryGetStringField(TEXT("lobbyId"), F_lobbyId))
	{
		Target.lobbyId = F_lobbyId;
	}

	FString F_sessionId;
	if (obj->TryGetStringField(TEXT("sessionId"), F_sessionId))
	{
		Target.sessionId = F_sessionId;
	}


	return Target;
}



Ulobby_Lobby_lobbiesPaginatedGET::Ulobby_Lobby_lobbiesPaginatedGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_lobbiesPaginatedGET* Ulobby_Lobby_lobbiesPaginatedGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit
)
{
	Ulobby_Lobby_lobbiesPaginatedGET* Proxy = NewObject<Ulobby_Lobby_lobbiesPaginatedGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;


	return Proxy;
}

void Ulobby_Lobby_lobbiesPaginatedGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /lobbies/paginated get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/lobbies/paginated?start=%s&limit=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_lobbiesPaginatedGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies/paginated get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies/paginated get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_PaginatedGameLobbies(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /lobbies/paginated get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies/paginated get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_PaginatedGameLobbies(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies/paginated get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_PaginatedGameLobbies(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies/paginated get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_PaginatedGameLobbies(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivelobby_PaginatedGameLobbies(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /lobbies/paginated get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies/paginated get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_PaginatedGameLobbies(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_lobbiesPaginatedGET>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_lobbiesGET::Ulobby_Lobby_lobbiesGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_lobbiesGET* Ulobby_Lobby_lobbiesGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Ulobby_Lobby_lobbiesGET* Proxy = NewObject<Ulobby_Lobby_lobbiesGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Ulobby_Lobby_lobbiesGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /lobbies get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/lobbies?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_lobbiesGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHivelobby_LobbyInfo>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /lobbies get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHivelobby_LobbyInfo>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivelobby_LobbyInfo>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivelobby_LobbyInfo>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHivelobby_LobbyInfo> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHivelobby_LobbyInfo(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /lobbies get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobbies get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivelobby_LobbyInfo>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_lobbiesGET>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_lobbyGET::Ulobby_Lobby_lobbyGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_lobbyGET* Ulobby_Lobby_lobbyGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Ulobby_Lobby_lobbyGET* Proxy = NewObject<Ulobby_Lobby_lobbyGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Ulobby_Lobby_lobbyGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /lobby get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/lobby?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_lobbyGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /lobby get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivelobby_LobbyInfo(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /lobby get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_lobbyGET>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_lobbyPUT::Ulobby_Lobby_lobbyPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_lobbyPUT* Ulobby_Lobby_lobbyPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString name

	, int32 maxSessions
)
{
	Ulobby_Lobby_lobbyPUT* Proxy = NewObject<Ulobby_Lobby_lobbyPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_name = name;

	Proxy->Field_maxSessions = maxSessions;


	return Proxy;
}

void Ulobby_Lobby_lobbyPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /lobby put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/lobby?name=%s&maxSessions=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, this->Field_maxSessions

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_lobbyPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /lobby put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivelobby_LobbyInfo(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /lobby put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_lobbyPUT>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_lobbyPOST::Ulobby_Lobby_lobbyPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_lobbyPOST* Ulobby_Lobby_lobbyPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString name

	, int32 maxSessions
)
{
	Ulobby_Lobby_lobbyPOST* Proxy = NewObject<Ulobby_Lobby_lobbyPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_name = name;

	Proxy->Field_maxSessions = maxSessions;


	return Proxy;
}

void Ulobby_Lobby_lobbyPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /lobby post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/lobby?id=%s&name=%s&maxSessions=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, this->Field_maxSessions

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_lobbyPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /lobby post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivelobby_LobbyInfo(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /lobby post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_LobbyInfo(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_lobbyPOST>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_lobbyDELETE::Ulobby_Lobby_lobbyDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_lobbyDELETE* Ulobby_Lobby_lobbyDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Ulobby_Lobby_lobbyDELETE* Proxy = NewObject<Ulobby_Lobby_lobbyDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Ulobby_Lobby_lobbyDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /lobby delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/lobby?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_lobbyDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /lobby delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] lobby /lobby delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] lobby /lobby delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /lobby delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /lobby delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_lobbyDELETE>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_sessionsGET::Ulobby_Lobby_sessionsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_sessionsGET* Ulobby_Lobby_sessionsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Ulobby_Lobby_sessionsGET* Proxy = NewObject<Ulobby_Lobby_sessionsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Ulobby_Lobby_sessionsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /sessions get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/sessions?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_sessionsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /sessions get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /sessions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHivelobby_ConnectedSession>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /sessions get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /sessions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHivelobby_ConnectedSession>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /sessions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivelobby_ConnectedSession>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /sessions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivelobby_ConnectedSession>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHivelobby_ConnectedSession> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHivelobby_ConnectedSession(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /sessions get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /sessions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivelobby_ConnectedSession>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_sessionsGET>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_sessionGET::Ulobby_Lobby_sessionGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_sessionGET* Ulobby_Lobby_sessionGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString lobbyId

	, FString sessionId
)
{
	Ulobby_Lobby_sessionGET* Proxy = NewObject<Ulobby_Lobby_sessionGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_lobbyId = lobbyId;

	Proxy->Field_sessionId = sessionId;


	return Proxy;
}

void Ulobby_Lobby_sessionGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /session get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/session?lobbyId=%s&sessionId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_lobbyId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_sessionId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_sessionGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /session get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivelobby_ConnectedSession(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /session get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_sessionGET>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_sessionPUT::Ulobby_Lobby_sessionPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_sessionPUT* Ulobby_Lobby_sessionPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString lobbyId

	, FString sessionId
)
{
	Ulobby_Lobby_sessionPUT* Proxy = NewObject<Ulobby_Lobby_sessionPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_lobbyId = lobbyId;

	Proxy->Field_sessionId = sessionId;


	return Proxy;
}

void Ulobby_Lobby_sessionPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /session put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/session?lobbyId=%s&sessionId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_lobbyId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_sessionId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_sessionPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /session put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivelobby_ConnectedSession(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /session put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivelobby_ConnectedSession(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_sessionPUT>(this));
	HttpRequest->ProcessRequest();
}



Ulobby_Lobby_sessionDELETE::Ulobby_Lobby_sessionDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ulobby_Lobby_sessionDELETE* Ulobby_Lobby_sessionDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString lobbyId

	, FString sessionId
)
{
	Ulobby_Lobby_sessionDELETE* Proxy = NewObject<Ulobby_Lobby_sessionDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_lobbyId = lobbyId;

	Proxy->Field_sessionId = sessionId;


	return Proxy;
}

void Ulobby_Lobby_sessionDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] lobby /session delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://lobby-api.hivemp.com/v1/session?lobbyId=%s&sessionId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_lobbyId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_sessionId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ulobby_Lobby_sessionDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] lobby /session delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] lobby /session delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] lobby /session delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] lobby /session delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] lobby /session delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] lobby /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ulobby_Lobby_sessionDELETE>(this));
	HttpRequest->ProcessRequest();
}



struct FHivenat_punchthrough_NATNegotation DeserializeFHivenat_punchthrough_NATNegotation(const TSharedPtr<FJsonObject> obj)
{
	struct FHivenat_punchthrough_NATNegotation Target;
	

	FString F_host;
	if (obj->TryGetStringField(TEXT("host"), F_host))
	{
		Target.host = F_host;
	}

	double F_port;
	if (obj->TryGetNumberField(TEXT("port"), F_port))
	{
		Target.port = (int32)F_port;
	}

	FString F_message;
	if (obj->TryGetStringField(TEXT("message"), F_message))
	{
		FBase64::Decode(F_message, Target.message);
	}


	return Target;
}



struct FHivenat_punchthrough_NATEndpoint DeserializeFHivenat_punchthrough_NATEndpoint(const TSharedPtr<FJsonObject> obj)
{
	struct FHivenat_punchthrough_NATEndpoint Target;
	

	FString F_host;
	if (obj->TryGetStringField(TEXT("host"), F_host))
	{
		Target.host = F_host;
	}

	double F_port;
	if (obj->TryGetNumberField(TEXT("port"), F_port))
	{
		Target.port = (int32)F_port;
	}


	return Target;
}



Unat_punchthrough_Punchthrough_punchthroughGET::Unat_punchthrough_Punchthrough_punchthroughGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Unat_punchthrough_Punchthrough_punchthroughGET* Unat_punchthrough_Punchthrough_punchthroughGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString session
)
{
	Unat_punchthrough_Punchthrough_punchthroughGET* Proxy = NewObject<Unat_punchthrough_Punchthrough_punchthroughGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_session = session;


	return Proxy;
}

void Unat_punchthrough_Punchthrough_punchthroughGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] nat-punchthrough /punchthrough get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://nat-punchthrough-api.hivemp.com/v1/punchthrough?session=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_session)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Unat_punchthrough_Punchthrough_punchthroughGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] nat-punchthrough /punchthrough get: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] nat-punchthrough /punchthrough get"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] nat-punchthrough /punchthrough get"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] nat-punchthrough /punchthrough get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Unat_punchthrough_Punchthrough_punchthroughGET>(this));
	HttpRequest->ProcessRequest();
}



Unat_punchthrough_Punchthrough_punchthroughPUT::Unat_punchthrough_Punchthrough_punchthroughPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Unat_punchthrough_Punchthrough_punchthroughPUT* Unat_punchthrough_Punchthrough_punchthroughPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString session
)
{
	Unat_punchthrough_Punchthrough_punchthroughPUT* Proxy = NewObject<Unat_punchthrough_Punchthrough_punchthroughPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_session = session;


	return Proxy;
}

void Unat_punchthrough_Punchthrough_punchthroughPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] nat-punchthrough /punchthrough put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://nat-punchthrough-api.hivemp.com/v1/punchthrough?session=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_session)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Unat_punchthrough_Punchthrough_punchthroughPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivenat_punchthrough_NATNegotation(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] nat-punchthrough /punchthrough put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivenat_punchthrough_NATNegotation(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivenat_punchthrough_NATNegotation(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivenat_punchthrough_NATNegotation(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivenat_punchthrough_NATNegotation(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] nat-punchthrough /punchthrough put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /punchthrough put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivenat_punchthrough_NATNegotation(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Unat_punchthrough_Punchthrough_punchthroughPUT>(this));
	HttpRequest->ProcessRequest();
}



Unat_punchthrough_Punchthrough_endpointsGET::Unat_punchthrough_Punchthrough_endpointsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Unat_punchthrough_Punchthrough_endpointsGET* Unat_punchthrough_Punchthrough_endpointsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString session
)
{
	Unat_punchthrough_Punchthrough_endpointsGET* Proxy = NewObject<Unat_punchthrough_Punchthrough_endpointsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_session = session;


	return Proxy;
}

void Unat_punchthrough_Punchthrough_endpointsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] nat-punchthrough /endpoints get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://nat-punchthrough-api.hivemp.com/v1/endpoints?session=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_session)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Unat_punchthrough_Punchthrough_endpointsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /endpoints get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /endpoints get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHivenat_punchthrough_NATEndpoint>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] nat-punchthrough /endpoints get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /endpoints get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHivenat_punchthrough_NATEndpoint>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /endpoints get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivenat_punchthrough_NATEndpoint>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /endpoints get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivenat_punchthrough_NATEndpoint>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHivenat_punchthrough_NATEndpoint> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHivenat_punchthrough_NATEndpoint(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] nat-punchthrough /endpoints get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /endpoints get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHivenat_punchthrough_NATEndpoint>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Unat_punchthrough_Punchthrough_endpointsGET>(this));
	HttpRequest->ProcessRequest();
}



Unat_punchthrough_Punchthrough_pingPUT::Unat_punchthrough_Punchthrough_pingPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Unat_punchthrough_Punchthrough_pingPUT* Unat_punchthrough_Punchthrough_pingPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString sessionId

	, FString hashedSecretKey

	, FString address

	, int32 port
)
{
	Unat_punchthrough_Punchthrough_pingPUT* Proxy = NewObject<Unat_punchthrough_Punchthrough_pingPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_sessionId = sessionId;

	Proxy->Field_hashedSecretKey = hashedSecretKey;

	Proxy->Field_address = address;

	Proxy->Field_port = port;


	return Proxy;
}

void Unat_punchthrough_Punchthrough_pingPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] nat-punchthrough /ping put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://nat-punchthrough-api.hivemp.com/v1/ping?sessionId=%s&hashedSecretKey=%s&address=%s&port=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_sessionId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_hashedSecretKey)

		, *FGenericPlatformHttp::UrlEncode(this->Field_address)

		, this->Field_port

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Unat_punchthrough_Punchthrough_pingPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /ping put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /ping put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] nat-punchthrough /ping put: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] nat-punchthrough /ping put"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] nat-punchthrough /ping put"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /ping put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /ping put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /ping put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] nat-punchthrough /ping put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] nat-punchthrough /ping put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Unat_punchthrough_Punchthrough_pingPUT>(this));
	HttpRequest->ProcessRequest();
}



struct FHivereporting_TimeSeriesData DeserializeFHivereporting_TimeSeriesData(const TSharedPtr<FJsonObject> obj)
{
	struct FHivereporting_TimeSeriesData Target;
	

	double F_timeBegin;
	if (obj->TryGetNumberField(TEXT("timeBegin"), F_timeBegin))
	{
		Target.timeBegin = (int32)F_timeBegin;
	}

	double F_timeEnd;
	if (obj->TryGetNumberField(TEXT("timeEnd"), F_timeEnd))
	{
		Target.timeEnd = (int32)F_timeEnd;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_dataGroups;
	if (obj->TryGetArrayField(TEXT("dataGroups"), F_dataGroups))
	{
		for (int i = 0; i < F_dataGroups->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_dataGroups;
			if ((*F_dataGroups)[i]->TryGetObject(A_dataGroups))
			{
				Target.dataGroups.Add(DeserializeFHivereporting_DataGroup(*A_dataGroups));
			}

		}
	}

	FString F_dataPoints;
	if (obj->TryGetStringField(TEXT("dataPoints"), F_dataPoints))
	{
		Target.dataPoints = F_dataPoints;
	}


	return Target;
}



struct FHivereporting_DataGroup DeserializeFHivereporting_DataGroup(const TSharedPtr<FJsonObject> obj)
{
	struct FHivereporting_DataGroup Target;
	

	FString F_groupName;
	if (obj->TryGetStringField(TEXT("groupName"), F_groupName))
	{
		Target.groupName = F_groupName;
	}

	FString F_preferredColor;
	if (obj->TryGetStringField(TEXT("preferredColor"), F_preferredColor))
	{
		Target.preferredColor = F_preferredColor;
	}


	return Target;
}



struct FHivereporting_TimeSeriesDataPoint DeserializeFHivereporting_TimeSeriesDataPoint(const TSharedPtr<FJsonObject> obj)
{
	struct FHivereporting_TimeSeriesDataPoint Target;
	

	double F_integerValue;
	if (obj->TryGetNumberField(TEXT("integerValue"), F_integerValue))
	{
		Target.integerValue = (int32)F_integerValue;
	}

	double F_percentValue;
	if (obj->TryGetNumberField(TEXT("percentValue"), F_percentValue))
	{
		Target.percentValue = (float)F_percentValue;
	}

	double F_currencyUsdValue;
	if (obj->TryGetNumberField(TEXT("currencyUsdValue"), F_currencyUsdValue))
	{
		Target.currencyUsdValue = (float)F_currencyUsdValue;
	}


	return Target;
}



struct FHivereporting_PaginatedReportMetadatas DeserializeFHivereporting_PaginatedReportMetadatas(const TSharedPtr<FJsonObject> obj)
{
	struct FHivereporting_PaginatedReportMetadatas Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHivereporting_ReportMetadata(*A_results));
			}

		}
	}


	return Target;
}



struct FHivereporting_ReportMetadata DeserializeFHivereporting_ReportMetadata(const TSharedPtr<FJsonObject> obj)
{
	struct FHivereporting_ReportMetadata Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	bool F_available;
	if (obj->TryGetBoolField(TEXT("available"), F_available))
	{
		Target.available = (bool)F_available;
	}

	FString F_title;
	if (obj->TryGetStringField(TEXT("title"), F_title))
	{
		Target.title = F_title;
	}

	FString F_shortDescription;
	if (obj->TryGetStringField(TEXT("shortDescription"), F_shortDescription))
	{
		Target.shortDescription = F_shortDescription;
	}

	FString F_category;
	if (obj->TryGetStringField(TEXT("category"), F_category))
	{
		Target.category = F_category;
	}

	FString F_type;
	if (obj->TryGetStringField(TEXT("type"), F_type))
	{
		Target.type = F_type;
	}


	return Target;
}



struct FHivereporting_ReportData DeserializeFHivereporting_ReportData(const TSharedPtr<FJsonObject> obj)
{
	struct FHivereporting_ReportData Target;
	

	const TSharedPtr<FJsonObject>* F_metadata;
	if (obj->TryGetObjectField(TEXT("metadata"), F_metadata))
	{
		Target.metadata = DeserializeFHivereporting_ReportMetadata(*F_metadata);
	}

	const TSharedPtr<FJsonObject>* F_timeSeriesData;
	if (obj->TryGetObjectField(TEXT("timeSeriesData"), F_timeSeriesData))
	{
		Target.timeSeriesData = DeserializeFHivereporting_TimeSeriesData(*F_timeSeriesData);
	}


	return Target;
}



Ureporting_BuiltinReports_builtinVisitsWishlistsGET::Ureporting_BuiltinReports_builtinVisitsWishlistsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinVisitsWishlistsGET* Ureporting_BuiltinReports_builtinVisitsWishlistsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinVisitsWishlistsGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinVisitsWishlistsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinVisitsWishlistsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/visits/wishlists get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/visits/wishlists?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsWishlistsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/wishlists get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/wishlists get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/visits/wishlists get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/wishlists get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/wishlists get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/wishlists get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/visits/wishlists get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/wishlists get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsWishlistsGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinVisitsActionsGET::Ureporting_BuiltinReports_builtinVisitsActionsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinVisitsActionsGET* Ureporting_BuiltinReports_builtinVisitsActionsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinVisitsActionsGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinVisitsActionsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinVisitsActionsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/visits/actions get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/visits/actions?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsActionsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/visits/actions get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/visits/actions get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsActionsGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinVisitsActionsConversionGET::Ureporting_BuiltinReports_builtinVisitsActionsConversionGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinVisitsActionsConversionGET* Ureporting_BuiltinReports_builtinVisitsActionsConversionGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinVisitsActionsConversionGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinVisitsActionsConversionGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinVisitsActionsConversionGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/visits/actions/conversion get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/visits/actions/conversion?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsActionsConversionGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions/conversion get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions/conversion get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/visits/actions/conversion get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions/conversion get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions/conversion get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions/conversion get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/visits/actions/conversion get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/actions/conversion get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsActionsConversionGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinWishlistActionsGET::Ureporting_BuiltinReports_builtinWishlistActionsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinWishlistActionsGET* Ureporting_BuiltinReports_builtinWishlistActionsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinWishlistActionsGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinWishlistActionsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinWishlistActionsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/wishlist/actions get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/wishlist/actions?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinWishlistActionsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/wishlist/actions get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/wishlist/actions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/wishlist/actions get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/wishlist/actions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/wishlist/actions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/wishlist/actions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/wishlist/actions get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/wishlist/actions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinWishlistActionsGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET::Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET* Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/visits/breakdown/detailed get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/visits/breakdown/detailed?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/detailed get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/detailed get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/visits/breakdown/detailed get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/detailed get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/detailed get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/detailed get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/visits/breakdown/detailed get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/detailed get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET::Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET* Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/visits/breakdown/page get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/visits/breakdown/page?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/page get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/page get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/visits/breakdown/page get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/page get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/page get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/page get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/visits/breakdown/page get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/visits/breakdown/page get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET::Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET* Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/sales/unit/breakdown/source get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/sales/unit/breakdown/source?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/source get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/source get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/sales/unit/breakdown/source get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/source get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/source get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/source get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/sales/unit/breakdown/source get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/source get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET::Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET* Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/sales/unit/breakdown/steam get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/sales/unit/breakdown/steam?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/steam get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/steam get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/sales/unit/breakdown/steam get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/steam get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/steam get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/steam get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/sales/unit/breakdown/steam get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/steam get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET::Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET* Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/sales/unit/breakdown/retail get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/sales/unit/breakdown/retail?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/retail get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/retail get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/sales/unit/breakdown/retail get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/retail get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/retail get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/retail get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/sales/unit/breakdown/retail get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/unit/breakdown/retail get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET::Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET* Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/sales/usd/breakdown/source get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/sales/usd/breakdown/source?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/source get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/source get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/sales/usd/breakdown/source get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/source get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/source get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/source get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/sales/usd/breakdown/source get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/source get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET::Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET* Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, int32 start

	, int32 end

	, int32 intervalAmount

	, FString intervalUnits
)
{
	Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET* Proxy = NewObject<Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_intervalAmount = intervalAmount;

	Proxy->Field_intervalUnits = intervalUnits;


	return Proxy;
}

void Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /builtin/sales/usd/breakdown/steam get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/builtin/sales/usd/breakdown/steam?start=%i&end=%i&intervalAmount=%i&intervalUnits=%s")

		, this->Field_start

		, this->Field_end

		, this->Field_intervalAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_intervalUnits)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/steam get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/steam get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /builtin/sales/usd/breakdown/steam get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/steam get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/steam get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/steam get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_TimeSeriesData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /builtin/sales/usd/breakdown/steam get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /builtin/sales/usd/breakdown/steam get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_TimeSeriesData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_Report_reportsGET::Ureporting_Report_reportsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_Report_reportsGET* Ureporting_Report_reportsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit
)
{
	Ureporting_Report_reportsGET* Proxy = NewObject<Ureporting_Report_reportsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;


	return Proxy;
}

void Ureporting_Report_reportsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /reports get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/reports?start=%s&limit=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_Report_reportsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /reports get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /reports get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_PaginatedReportMetadatas(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /reports get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /reports get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_PaginatedReportMetadatas(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /reports get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_PaginatedReportMetadatas(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /reports get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_PaginatedReportMetadatas(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_PaginatedReportMetadatas(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /reports get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /reports get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_PaginatedReportMetadatas(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_Report_reportsGET>(this));
	HttpRequest->ProcessRequest();
}



Ureporting_Report_reportGET::Ureporting_Report_reportGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Ureporting_Report_reportGET* Ureporting_Report_reportGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, int32 start

	, int32 end

	, FString /* JSON STRING */ parameters
)
{
	Ureporting_Report_reportGET* Proxy = NewObject<Ureporting_Report_reportGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_start = start;

	Proxy->Field_end = end;

	Proxy->Field_parameters = parameters;


	return Proxy;
}

void Ureporting_Report_reportGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] reporting /report get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://reporting-api.hivemp.com/v1/report?id=%s&start=%i&end=%i&parameters=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, this->Field_start

		, this->Field_end

		, *FGenericPlatformHttp::UrlEncode(this->Field_parameters)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Ureporting_Report_reportGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /report get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /report get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_ReportData(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] reporting /report get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] reporting /report get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivereporting_ReportData(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /report get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_ReportData(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /report get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_ReportData(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivereporting_ReportData(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] reporting /report get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] reporting /report get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivereporting_ReportData(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Ureporting_Report_reportGET>(this));
	HttpRequest->ProcessRequest();
}



struct FHiverevenue_share_PaginatedInvoices DeserializeFHiverevenue_share_PaginatedInvoices(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_PaginatedInvoices Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHiverevenue_share_Invoice(*A_results));
			}

		}
	}


	return Target;
}



struct FHiverevenue_share_Invoice DeserializeFHiverevenue_share_Invoice(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_Invoice Target;
	

	FString F_invoiceId;
	if (obj->TryGetStringField(TEXT("invoiceId"), F_invoiceId))
	{
		Target.invoiceId = F_invoiceId;
	}

	double F_dateCreatedUtc;
	if (obj->TryGetNumberField(TEXT("dateCreatedUtc"), F_dateCreatedUtc))
	{
		Target.dateCreatedUtc = (int32)F_dateCreatedUtc;
	}

	FString F_invoiceNumber;
	if (obj->TryGetStringField(TEXT("invoiceNumber"), F_invoiceNumber))
	{
		Target.invoiceNumber = F_invoiceNumber;
	}

	FString F_notes;
	if (obj->TryGetStringField(TEXT("notes"), F_notes))
	{
		Target.notes = F_notes;
	}

	FString F_invoicePostId;
	if (obj->TryGetStringField(TEXT("invoicePostId"), F_invoicePostId))
	{
		Target.invoicePostId = F_invoicePostId;
	}

	double F_invoicePostedUtc;
	if (obj->TryGetNumberField(TEXT("invoicePostedUtc"), F_invoicePostedUtc))
	{
		Target.invoicePostedUtc = (int32)F_invoicePostedUtc;
	}

	FString F_invoicePostNotes;
	if (obj->TryGetStringField(TEXT("invoicePostNotes"), F_invoicePostNotes))
	{
		Target.invoicePostNotes = F_invoicePostNotes;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_lineItems;
	if (obj->TryGetArrayField(TEXT("lineItems"), F_lineItems))
	{
		for (int i = 0; i < F_lineItems->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_lineItems;
			if ((*F_lineItems)[i]->TryGetObject(A_lineItems))
			{
				Target.lineItems.Add(DeserializeFHiverevenue_share_InvoiceLineItem(*A_lineItems));
			}

		}
	}


	return Target;
}



struct FHiverevenue_share_InvoiceLineItem DeserializeFHiverevenue_share_InvoiceLineItem(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_InvoiceLineItem Target;
	

	FString F_invoiceId;
	if (obj->TryGetStringField(TEXT("invoiceId"), F_invoiceId))
	{
		Target.invoiceId = F_invoiceId;
	}

	FString F_invoiceLineItemId;
	if (obj->TryGetStringField(TEXT("invoiceLineItemId"), F_invoiceLineItemId))
	{
		Target.invoiceLineItemId = F_invoiceLineItemId;
	}

	FString F_productId;
	if (obj->TryGetStringField(TEXT("productId"), F_productId))
	{
		Target.productId = F_productId;
	}

	FString F_productName;
	if (obj->TryGetStringField(TEXT("productName"), F_productName))
	{
		Target.productName = F_productName;
	}

	FString F_revenueRulesetIdOverride;
	if (obj->TryGetStringField(TEXT("revenueRulesetIdOverride"), F_revenueRulesetIdOverride))
	{
		Target.revenueRulesetIdOverride = F_revenueRulesetIdOverride;
	}

	double F_amount;
	if (obj->TryGetNumberField(TEXT("amount"), F_amount))
	{
		Target.amount = (int32)F_amount;
	}

	double F_amountFractionalDivisor;
	if (obj->TryGetNumberField(TEXT("amountFractionalDivisor"), F_amountFractionalDivisor))
	{
		Target.amountFractionalDivisor = (int32)F_amountFractionalDivisor;
	}

	FString F_currency;
	if (obj->TryGetStringField(TEXT("currency"), F_currency))
	{
		Target.currency = F_currency;
	}

	double F_amountPaid;
	if (obj->TryGetNumberField(TEXT("amountPaid"), F_amountPaid))
	{
		Target.amountPaid = (int32)F_amountPaid;
	}

	double F_amountPaidFractionalDivisor;
	if (obj->TryGetNumberField(TEXT("amountPaidFractionalDivisor"), F_amountPaidFractionalDivisor))
	{
		Target.amountPaidFractionalDivisor = (int32)F_amountPaidFractionalDivisor;
	}

	bool F_hasRevenueShareRulesetCopy;
	if (obj->TryGetBoolField(TEXT("hasRevenueShareRulesetCopy"), F_hasRevenueShareRulesetCopy))
	{
		Target.hasRevenueShareRulesetCopy = (bool)F_hasRevenueShareRulesetCopy;
	}


	return Target;
}



struct FHiverevenue_share_PaginatedInvoicePayments DeserializeFHiverevenue_share_PaginatedInvoicePayments(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_PaginatedInvoicePayments Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHiverevenue_share_InvoicePayment(*A_results));
			}

		}
	}


	return Target;
}



struct FHiverevenue_share_InvoicePayment DeserializeFHiverevenue_share_InvoicePayment(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_InvoicePayment Target;
	

	FString F_paymentId;
	if (obj->TryGetStringField(TEXT("paymentId"), F_paymentId))
	{
		Target.paymentId = F_paymentId;
	}

	FString F_invoiceId;
	if (obj->TryGetStringField(TEXT("invoiceId"), F_invoiceId))
	{
		Target.invoiceId = F_invoiceId;
	}

	double F_dateCreatedUtc;
	if (obj->TryGetNumberField(TEXT("dateCreatedUtc"), F_dateCreatedUtc))
	{
		Target.dateCreatedUtc = (int32)F_dateCreatedUtc;
	}

	FString F_paymentNumber;
	if (obj->TryGetStringField(TEXT("paymentNumber"), F_paymentNumber))
	{
		Target.paymentNumber = F_paymentNumber;
	}

	FString F_notes;
	if (obj->TryGetStringField(TEXT("notes"), F_notes))
	{
		Target.notes = F_notes;
	}

	FString F_invoicePostId;
	if (obj->TryGetStringField(TEXT("invoicePostId"), F_invoicePostId))
	{
		Target.invoicePostId = F_invoicePostId;
	}

	FString F_paymentPostId;
	if (obj->TryGetStringField(TEXT("paymentPostId"), F_paymentPostId))
	{
		Target.paymentPostId = F_paymentPostId;
	}

	double F_paymentPostedUtc;
	if (obj->TryGetNumberField(TEXT("paymentPostedUtc"), F_paymentPostedUtc))
	{
		Target.paymentPostedUtc = (int32)F_paymentPostedUtc;
	}

	FString F_paymentPostNotes;
	if (obj->TryGetStringField(TEXT("paymentPostNotes"), F_paymentPostNotes))
	{
		Target.paymentPostNotes = F_paymentPostNotes;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_lineItems;
	if (obj->TryGetArrayField(TEXT("lineItems"), F_lineItems))
	{
		for (int i = 0; i < F_lineItems->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_lineItems;
			if ((*F_lineItems)[i]->TryGetObject(A_lineItems))
			{
				Target.lineItems.Add(DeserializeFHiverevenue_share_InvoicePaymentLineItem(*A_lineItems));
			}

		}
	}

	bool F_archived;
	if (obj->TryGetBoolField(TEXT("archived"), F_archived))
	{
		Target.archived = (bool)F_archived;
	}


	return Target;
}



struct FHiverevenue_share_InvoicePaymentLineItem DeserializeFHiverevenue_share_InvoicePaymentLineItem(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_InvoicePaymentLineItem Target;
	

	FString F_paymentId;
	if (obj->TryGetStringField(TEXT("paymentId"), F_paymentId))
	{
		Target.paymentId = F_paymentId;
	}

	FString F_invoiceLineItemId;
	if (obj->TryGetStringField(TEXT("invoiceLineItemId"), F_invoiceLineItemId))
	{
		Target.invoiceLineItemId = F_invoiceLineItemId;
	}

	double F_amount;
	if (obj->TryGetNumberField(TEXT("amount"), F_amount))
	{
		Target.amount = (int32)F_amount;
	}

	double F_amountFractionalDivisor;
	if (obj->TryGetNumberField(TEXT("amountFractionalDivisor"), F_amountFractionalDivisor))
	{
		Target.amountFractionalDivisor = (int32)F_amountFractionalDivisor;
	}

	double F_sourceAmount;
	if (obj->TryGetNumberField(TEXT("sourceAmount"), F_sourceAmount))
	{
		Target.sourceAmount = (int32)F_sourceAmount;
	}

	double F_sourceAmountFractionalDivisor;
	if (obj->TryGetNumberField(TEXT("sourceAmountFractionalDivisor"), F_sourceAmountFractionalDivisor))
	{
		Target.sourceAmountFractionalDivisor = (int32)F_sourceAmountFractionalDivisor;
	}

	FString F_sourceCurrency;
	if (obj->TryGetStringField(TEXT("sourceCurrency"), F_sourceCurrency))
	{
		Target.sourceCurrency = F_sourceCurrency;
	}

	double F_exchangeRate;
	if (obj->TryGetNumberField(TEXT("exchangeRate"), F_exchangeRate))
	{
		Target.exchangeRate = (float)F_exchangeRate;
	}


	return Target;
}



struct FHiverevenue_share_RecipientTransaction DeserializeFHiverevenue_share_RecipientTransaction(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_RecipientTransaction Target;
	

	FString F_transactionId;
	if (obj->TryGetStringField(TEXT("transactionId"), F_transactionId))
	{
		Target.transactionId = F_transactionId;
	}

	FString F_postId;
	if (obj->TryGetStringField(TEXT("postId"), F_postId))
	{
		Target.postId = F_postId;
	}

	FString F_recipientId;
	if (obj->TryGetStringField(TEXT("recipientId"), F_recipientId))
	{
		Target.recipientId = F_recipientId;
	}

	FString F_recipientName;
	if (obj->TryGetStringField(TEXT("recipientName"), F_recipientName))
	{
		Target.recipientName = F_recipientName;
	}

	FString F_invoiceId;
	if (obj->TryGetStringField(TEXT("invoiceId"), F_invoiceId))
	{
		Target.invoiceId = F_invoiceId;
	}

	FString F_paymentId;
	if (obj->TryGetStringField(TEXT("paymentId"), F_paymentId))
	{
		Target.paymentId = F_paymentId;
	}

	double F_amount;
	if (obj->TryGetNumberField(TEXT("amount"), F_amount))
	{
		Target.amount = (int32)F_amount;
	}

	double F_amountFractionalDivisor;
	if (obj->TryGetNumberField(TEXT("amountFractionalDivisor"), F_amountFractionalDivisor))
	{
		Target.amountFractionalDivisor = (int32)F_amountFractionalDivisor;
	}

	FString F_currency;
	if (obj->TryGetStringField(TEXT("currency"), F_currency))
	{
		Target.currency = F_currency;
	}


	return Target;
}



struct FHiverevenue_share_PaginatedProducts DeserializeFHiverevenue_share_PaginatedProducts(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_PaginatedProducts Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHiverevenue_share_Product(*A_results));
			}

		}
	}


	return Target;
}



struct FHiverevenue_share_Product DeserializeFHiverevenue_share_Product(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_Product Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_name;
	if (obj->TryGetStringField(TEXT("name"), F_name))
	{
		Target.name = F_name;
	}

	FString F_description;
	if (obj->TryGetStringField(TEXT("description"), F_description))
	{
		Target.description = F_description;
	}

	bool F_visible;
	if (obj->TryGetBoolField(TEXT("visible"), F_visible))
	{
		Target.visible = (bool)F_visible;
	}

	FString F_tags;
	if (obj->TryGetStringField(TEXT("tags"), F_tags))
	{
		Target.tags = F_tags;
	}

	FString F_defaultRevenueShareRulesetId;
	if (obj->TryGetStringField(TEXT("defaultRevenueShareRulesetId"), F_defaultRevenueShareRulesetId))
	{
		Target.defaultRevenueShareRulesetId = F_defaultRevenueShareRulesetId;
	}

	FString F_dataCaptureProjectId;
	if (obj->TryGetStringField(TEXT("dataCaptureProjectId"), F_dataCaptureProjectId))
	{
		Target.dataCaptureProjectId = F_dataCaptureProjectId;
	}


	return Target;
}



struct FHiverevenue_share_ProductSearchResult DeserializeFHiverevenue_share_ProductSearchResult(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_ProductSearchResult Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_name;
	if (obj->TryGetStringField(TEXT("name"), F_name))
	{
		Target.name = F_name;
	}


	return Target;
}



struct FHiverevenue_share_PaginatedRecipients DeserializeFHiverevenue_share_PaginatedRecipients(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_PaginatedRecipients Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHiverevenue_share_Recipient(*A_results));
			}

		}
	}


	return Target;
}



struct FHiverevenue_share_Recipient DeserializeFHiverevenue_share_Recipient(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_Recipient Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_name;
	if (obj->TryGetStringField(TEXT("name"), F_name))
	{
		Target.name = F_name;
	}

	FString F_description;
	if (obj->TryGetStringField(TEXT("description"), F_description))
	{
		Target.description = F_description;
	}

	double F_postDistributionTaxPercentage;
	if (obj->TryGetNumberField(TEXT("postDistributionTaxPercentage"), F_postDistributionTaxPercentage))
	{
		Target.postDistributionTaxPercentage = (int32)F_postDistributionTaxPercentage;
	}

	double F_startingBalance;
	if (obj->TryGetNumberField(TEXT("startingBalance"), F_startingBalance))
	{
		Target.startingBalance = (int32)F_startingBalance;
	}

	bool F_trackBalanceAndPayments;
	if (obj->TryGetBoolField(TEXT("trackBalanceAndPayments"), F_trackBalanceAndPayments))
	{
		Target.trackBalanceAndPayments = (bool)F_trackBalanceAndPayments;
	}

	bool F_visible;
	if (obj->TryGetBoolField(TEXT("visible"), F_visible))
	{
		Target.visible = (bool)F_visible;
	}


	return Target;
}



struct FHiverevenue_share_RecipientSearchResult DeserializeFHiverevenue_share_RecipientSearchResult(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_RecipientSearchResult Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_name;
	if (obj->TryGetStringField(TEXT("name"), F_name))
	{
		Target.name = F_name;
	}


	return Target;
}



struct FHiverevenue_share_PaginatedRevenueShareRulesets DeserializeFHiverevenue_share_PaginatedRevenueShareRulesets(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_PaginatedRevenueShareRulesets Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHiverevenue_share_RevenueShareRuleset(*A_results));
			}

		}
	}


	return Target;
}



struct FHiverevenue_share_RevenueShareRuleset DeserializeFHiverevenue_share_RevenueShareRuleset(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_RevenueShareRuleset Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_name;
	if (obj->TryGetStringField(TEXT("name"), F_name))
	{
		Target.name = F_name;
	}

	FString F_description;
	if (obj->TryGetStringField(TEXT("description"), F_description))
	{
		Target.description = F_description;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_ruleset;
	if (obj->TryGetArrayField(TEXT("ruleset"), F_ruleset))
	{
		for (int i = 0; i < F_ruleset->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_ruleset;
			if ((*F_ruleset)[i]->TryGetObject(A_ruleset))
			{
				Target.ruleset.Add(DeserializeFHiverevenue_share_RevenueShareRulesetRule(*A_ruleset));
			}

		}
	}

	bool F_visible;
	if (obj->TryGetBoolField(TEXT("visible"), F_visible))
	{
		Target.visible = (bool)F_visible;
	}


	return Target;
}



struct FHiverevenue_share_RevenueShareRulesetRule DeserializeFHiverevenue_share_RevenueShareRulesetRule(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_RevenueShareRulesetRule Target;
	

	const TArray<TSharedPtr<FJsonValue>>* F_distributions;
	if (obj->TryGetArrayField(TEXT("distributions"), F_distributions))
	{
		for (int i = 0; i < F_distributions->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_distributions;
			if ((*F_distributions)[i]->TryGetObject(A_distributions))
			{
				Target.distributions.Add(DeserializeFHiverevenue_share_RevenueShareRulesetDistribution(*A_distributions));
			}

		}
	}

	FString F_sourceFilters;
	if (obj->TryGetStringField(TEXT("sourceFilters"), F_sourceFilters))
	{
		Target.sourceFilters = F_sourceFilters;
	}


	return Target;
}



struct FHiverevenue_share_RevenueShareRulesetDistribution DeserializeFHiverevenue_share_RevenueShareRulesetDistribution(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_RevenueShareRulesetDistribution Target;
	

	FString F_recipientId;
	if (obj->TryGetStringField(TEXT("recipientId"), F_recipientId))
	{
		Target.recipientId = F_recipientId;
	}

	double F_percentageAmount;
	if (obj->TryGetNumberField(TEXT("percentageAmount"), F_percentageAmount))
	{
		Target.percentageAmount = (float)F_percentageAmount;
	}

	double F_fixedAmount;
	if (obj->TryGetNumberField(TEXT("fixedAmount"), F_fixedAmount))
	{
		Target.fixedAmount = (int32)F_fixedAmount;
	}

	double F_paymentLimit;
	if (obj->TryGetNumberField(TEXT("paymentLimit"), F_paymentLimit))
	{
		Target.paymentLimit = (int32)F_paymentLimit;
	}

	bool F_distributeFromSourceAmount;
	if (obj->TryGetBoolField(TEXT("distributeFromSourceAmount"), F_distributeFromSourceAmount))
	{
		Target.distributeFromSourceAmount = (bool)F_distributeFromSourceAmount;
	}


	return Target;
}



struct FHiverevenue_share_RevenueShareRulesetSearchResult DeserializeFHiverevenue_share_RevenueShareRulesetSearchResult(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_RevenueShareRulesetSearchResult Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_name;
	if (obj->TryGetStringField(TEXT("name"), F_name))
	{
		Target.name = F_name;
	}


	return Target;
}



struct FHiverevenue_share_SimulatedPayment DeserializeFHiverevenue_share_SimulatedPayment(const TSharedPtr<FJsonObject> obj)
{
	struct FHiverevenue_share_SimulatedPayment Target;
	

	FString F_recipientId;
	if (obj->TryGetStringField(TEXT("recipientId"), F_recipientId))
	{
		Target.recipientId = F_recipientId;
	}

	FString F_recipientName;
	if (obj->TryGetStringField(TEXT("recipientName"), F_recipientName))
	{
		Target.recipientName = F_recipientName;
	}

	double F_amount;
	if (obj->TryGetNumberField(TEXT("amount"), F_amount))
	{
		Target.amount = (float)F_amount;
	}

	FString F_currency;
	if (obj->TryGetStringField(TEXT("currency"), F_currency))
	{
		Target.currency = F_currency;
	}


	return Target;
}



Urevenue_share_Invoice_invoicesGET::Urevenue_share_Invoice_invoicesGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicesGET* Urevenue_share_Invoice_invoicesGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit
)
{
	Urevenue_share_Invoice_invoicesGET* Proxy = NewObject<Urevenue_share_Invoice_invoicesGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;


	return Proxy;
}

void Urevenue_share_Invoice_invoicesGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoices get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoices?start=%s&limit=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicesGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoices get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoices get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoices(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoices get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoices get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoices(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoices get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoices(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoices get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoices(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_PaginatedInvoices(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoices get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoices get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoices(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicesGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoiceGET::Urevenue_share_Invoice_invoiceGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoiceGET* Urevenue_share_Invoice_invoiceGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId
)
{
	Urevenue_share_Invoice_invoiceGET* Proxy = NewObject<Urevenue_share_Invoice_invoiceGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;


	return Proxy;
}

void Urevenue_share_Invoice_invoiceGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice?invoiceId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoiceGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Invoice(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoiceGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePUT::Urevenue_share_Invoice_invoicePUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePUT* Urevenue_share_Invoice_invoicePUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceNumber

	, FString notes
)
{
	Urevenue_share_Invoice_invoicePUT* Proxy = NewObject<Urevenue_share_Invoice_invoicePUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceNumber = invoiceNumber;

	Proxy->Field_notes = notes;


	return Proxy;
}

void Urevenue_share_Invoice_invoicePUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice?invoiceNumber=%s&notes=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceNumber)

		, *FGenericPlatformHttp::UrlEncode(this->Field_notes)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Invoice(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePOST::Urevenue_share_Invoice_invoicePOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePOST* Urevenue_share_Invoice_invoicePOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId

	, FString invoiceNumber

	, FString notes
)
{
	Urevenue_share_Invoice_invoicePOST* Proxy = NewObject<Urevenue_share_Invoice_invoicePOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;

	Proxy->Field_invoiceNumber = invoiceNumber;

	Proxy->Field_notes = notes;


	return Proxy;
}

void Urevenue_share_Invoice_invoicePOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice?invoiceId=%s&invoiceNumber=%s&notes=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceNumber)

		, *FGenericPlatformHttp::UrlEncode(this->Field_notes)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Invoice(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePOST>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePostPUT::Urevenue_share_Invoice_invoicePostPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePostPUT* Urevenue_share_Invoice_invoicePostPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId

	, FString postNotes
)
{
	Urevenue_share_Invoice_invoicePostPUT* Proxy = NewObject<Urevenue_share_Invoice_invoicePostPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;

	Proxy->Field_postNotes = postNotes;


	return Proxy;
}

void Urevenue_share_Invoice_invoicePostPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/post put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/post?invoiceId=%s&postNotes=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_postNotes)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePostPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/post put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/post put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/post put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/post put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/post put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/post put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Invoice(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/post put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/post put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePostPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoiceUnpostPUT::Urevenue_share_Invoice_invoiceUnpostPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoiceUnpostPUT* Urevenue_share_Invoice_invoiceUnpostPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId
)
{
	Urevenue_share_Invoice_invoiceUnpostPUT* Proxy = NewObject<Urevenue_share_Invoice_invoiceUnpostPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;


	return Proxy;
}

void Urevenue_share_Invoice_invoiceUnpostPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/unpost put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/unpost?invoiceId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoiceUnpostPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/unpost put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/unpost put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/unpost put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/unpost put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/unpost put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/unpost put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Invoice(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/unpost put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/unpost put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Invoice(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoiceUnpostPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoiceItemPUT::Urevenue_share_Invoice_invoiceItemPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoiceItemPUT* Urevenue_share_Invoice_invoiceItemPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId

	, FString productId

	, FString revenueRulesetIdOverride

	, int32 amount

	, int32 amountFractionalDivisor

	, FString currency
)
{
	Urevenue_share_Invoice_invoiceItemPUT* Proxy = NewObject<Urevenue_share_Invoice_invoiceItemPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;

	Proxy->Field_productId = productId;

	Proxy->Field_revenueRulesetIdOverride = revenueRulesetIdOverride;

	Proxy->Field_amount = amount;

	Proxy->Field_amountFractionalDivisor = amountFractionalDivisor;

	Proxy->Field_currency = currency;


	return Proxy;
}

void Urevenue_share_Invoice_invoiceItemPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/item put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/item?invoiceId=%s&productId=%s&revenueRulesetIdOverride=%s&amount=%i&amountFractionalDivisor=%i&currency=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_productId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_revenueRulesetIdOverride)

		, this->Field_amount

		, this->Field_amountFractionalDivisor

		, *FGenericPlatformHttp::UrlEncode(this->Field_currency)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoiceItemPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/item put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_InvoiceLineItem(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/item put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoiceItemPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoiceItemPOST::Urevenue_share_Invoice_invoiceItemPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoiceItemPOST* Urevenue_share_Invoice_invoiceItemPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId

	, FString invoiceLineItemId

	, FString productId

	, FString revenueRulesetIdOverride

	, int32 amount

	, int32 amountFractionalDivisor

	, FString currency
)
{
	Urevenue_share_Invoice_invoiceItemPOST* Proxy = NewObject<Urevenue_share_Invoice_invoiceItemPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;

	Proxy->Field_invoiceLineItemId = invoiceLineItemId;

	Proxy->Field_productId = productId;

	Proxy->Field_revenueRulesetIdOverride = revenueRulesetIdOverride;

	Proxy->Field_amount = amount;

	Proxy->Field_amountFractionalDivisor = amountFractionalDivisor;

	Proxy->Field_currency = currency;


	return Proxy;
}

void Urevenue_share_Invoice_invoiceItemPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/item post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/item?invoiceId=%s&invoiceLineItemId=%s&productId=%s&revenueRulesetIdOverride=%s&amount=%i&amountFractionalDivisor=%i&currency=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceLineItemId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_productId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_revenueRulesetIdOverride)

		, this->Field_amount

		, this->Field_amountFractionalDivisor

		, *FGenericPlatformHttp::UrlEncode(this->Field_currency)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoiceItemPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/item post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_InvoiceLineItem(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/item post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoiceLineItem(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoiceItemPOST>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoiceItemDELETE::Urevenue_share_Invoice_invoiceItemDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoiceItemDELETE* Urevenue_share_Invoice_invoiceItemDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId

	, FString invoiceLineItemId
)
{
	Urevenue_share_Invoice_invoiceItemDELETE* Proxy = NewObject<Urevenue_share_Invoice_invoiceItemDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;

	Proxy->Field_invoiceLineItemId = invoiceLineItemId;


	return Proxy;
}

void Urevenue_share_Invoice_invoiceItemDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/item delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/item?invoiceId=%s&invoiceLineItemId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceLineItemId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoiceItemDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/item delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/item delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/item delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/item delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/item delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoiceItemDELETE>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePaymentsGET::Urevenue_share_Invoice_invoicePaymentsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePaymentsGET* Urevenue_share_Invoice_invoicePaymentsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId

	, FString start

	, int32 limit
)
{
	Urevenue_share_Invoice_invoicePaymentsGET* Proxy = NewObject<Urevenue_share_Invoice_invoicePaymentsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;

	Proxy->Field_start = start;

	Proxy->Field_limit = limit;


	return Proxy;
}

void Urevenue_share_Invoice_invoicePaymentsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/payments get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/payments?invoiceId=%s&start=%s&limit=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payments get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payments get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoicePayments(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/payments get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payments get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoicePayments(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payments get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoicePayments(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payments get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoicePayments(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_PaginatedInvoicePayments(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/payments get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payments get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedInvoicePayments(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentsGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePaymentGET::Urevenue_share_Invoice_invoicePaymentGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePaymentGET* Urevenue_share_Invoice_invoicePaymentGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString paymentId
)
{
	Urevenue_share_Invoice_invoicePaymentGET* Proxy = NewObject<Urevenue_share_Invoice_invoicePaymentGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_paymentId = paymentId;


	return Proxy;
}

void Urevenue_share_Invoice_invoicePaymentGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/payment get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/payment?paymentId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_paymentId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/payment get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_InvoicePayment(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/payment get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePaymentPUT::Urevenue_share_Invoice_invoicePaymentPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePaymentPUT* Urevenue_share_Invoice_invoicePaymentPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString invoiceId

	, FString paymentNumber

	, FString notes

	, TArray<FHiverevenue_share_InvoicePaymentLineItem> lineItems
)
{
	Urevenue_share_Invoice_invoicePaymentPUT* Proxy = NewObject<Urevenue_share_Invoice_invoicePaymentPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_invoiceId = invoiceId;

	Proxy->Field_paymentNumber = paymentNumber;

	Proxy->Field_notes = notes;

	Proxy->Field_lineItems = TArray<FHiverevenue_share_InvoicePaymentLineItem>(lineItems);


	return Proxy;
}

void Urevenue_share_Invoice_invoicePaymentPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/payment put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/payment?invoiceId=%s&paymentNumber=%s&notes=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_invoiceId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_paymentNumber)

		, *FGenericPlatformHttp::UrlEncode(this->Field_notes)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/payment put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_InvoicePayment(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/payment put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePaymentPOST::Urevenue_share_Invoice_invoicePaymentPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePaymentPOST* Urevenue_share_Invoice_invoicePaymentPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString paymentId

	, FString paymentNumber

	, FString notes

	, TArray<FHiverevenue_share_InvoicePaymentLineItem> lineItems
)
{
	Urevenue_share_Invoice_invoicePaymentPOST* Proxy = NewObject<Urevenue_share_Invoice_invoicePaymentPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_paymentId = paymentId;

	Proxy->Field_paymentNumber = paymentNumber;

	Proxy->Field_notes = notes;

	Proxy->Field_lineItems = TArray<FHiverevenue_share_InvoicePaymentLineItem>(lineItems);


	return Proxy;
}

void Urevenue_share_Invoice_invoicePaymentPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/payment post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/payment?paymentId=%s&paymentNumber=%s&notes=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_paymentId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_paymentNumber)

		, *FGenericPlatformHttp::UrlEncode(this->Field_notes)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/payment post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_InvoicePayment(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/payment post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentPOST>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePaymentPostPUT::Urevenue_share_Invoice_invoicePaymentPostPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePaymentPostPUT* Urevenue_share_Invoice_invoicePaymentPostPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString paymentId

	, FString postNotes
)
{
	Urevenue_share_Invoice_invoicePaymentPostPUT* Proxy = NewObject<Urevenue_share_Invoice_invoicePaymentPostPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_paymentId = paymentId;

	Proxy->Field_postNotes = postNotes;


	return Proxy;
}

void Urevenue_share_Invoice_invoicePaymentPostPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/payment/post put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/payment/post?paymentId=%s&postNotes=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_paymentId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_postNotes)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentPostPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/post put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/post put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/payment/post put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/post put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/post put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/post put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_InvoicePayment(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/payment/post put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/post put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentPostPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePaymentUnpostPUT::Urevenue_share_Invoice_invoicePaymentUnpostPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePaymentUnpostPUT* Urevenue_share_Invoice_invoicePaymentUnpostPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString paymentId
)
{
	Urevenue_share_Invoice_invoicePaymentUnpostPUT* Proxy = NewObject<Urevenue_share_Invoice_invoicePaymentUnpostPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_paymentId = paymentId;


	return Proxy;
}

void Urevenue_share_Invoice_invoicePaymentUnpostPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/payment/unpost put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/payment/unpost?paymentId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_paymentId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentUnpostPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/unpost put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/unpost put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/payment/unpost put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/unpost put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/unpost put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/unpost put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_InvoicePayment(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/payment/unpost put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/unpost put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_InvoicePayment(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentUnpostPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Invoice_invoicePaymentTransactionsGET::Urevenue_share_Invoice_invoicePaymentTransactionsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Invoice_invoicePaymentTransactionsGET* Urevenue_share_Invoice_invoicePaymentTransactionsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString paymentId
)
{
	Urevenue_share_Invoice_invoicePaymentTransactionsGET* Proxy = NewObject<Urevenue_share_Invoice_invoicePaymentTransactionsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_paymentId = paymentId;


	return Proxy;
}

void Urevenue_share_Invoice_invoicePaymentTransactionsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /invoice/payment/transactions get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/invoice/payment/transactions?paymentId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_paymentId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentTransactionsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/transactions get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/transactions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientTransaction>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /invoice/payment/transactions get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/transactions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientTransaction>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/transactions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientTransaction>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/transactions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientTransaction>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiverevenue_share_RecipientTransaction> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiverevenue_share_RecipientTransaction(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /invoice/payment/transactions get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /invoice/payment/transactions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientTransaction>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Invoice_invoicePaymentTransactionsGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Product_productsGET::Urevenue_share_Product_productsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Product_productsGET* Urevenue_share_Product_productsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit

	, bool showHidden
)
{
	Urevenue_share_Product_productsGET* Proxy = NewObject<Urevenue_share_Product_productsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;

	Proxy->Field_showHidden = showHidden;


	return Proxy;
}

void Urevenue_share_Product_productsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /products get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/products?start=%s&limit=%i&showHidden=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		, *FGenericPlatformHttp::UrlEncode(this->Field_showHidden ? TEXT("true") : TEXT("false"))

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Product_productsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedProducts(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /products get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedProducts(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedProducts(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedProducts(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_PaginatedProducts(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /products get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedProducts(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Product_productsGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Product_productsSearchGET::Urevenue_share_Product_productsSearchGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Product_productsSearchGET* Urevenue_share_Product_productsSearchGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString text
)
{
	Urevenue_share_Product_productsSearchGET* Proxy = NewObject<Urevenue_share_Product_productsSearchGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_text = text;


	return Proxy;
}

void Urevenue_share_Product_productsSearchGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /products/search get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/products/search?text=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_text)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Product_productsSearchGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products/search get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products/search get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_ProductSearchResult>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /products/search get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products/search get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_ProductSearchResult>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_ProductSearchResult>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_ProductSearchResult>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiverevenue_share_ProductSearchResult> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiverevenue_share_ProductSearchResult(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /products/search get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /products/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_ProductSearchResult>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Product_productsSearchGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Product_productGET::Urevenue_share_Product_productGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Product_productGET* Urevenue_share_Product_productGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Urevenue_share_Product_productGET* Proxy = NewObject<Urevenue_share_Product_productGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Urevenue_share_Product_productGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /product get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/product?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Product_productGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /product get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Product(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /product get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Product_productGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Product_productPUT::Urevenue_share_Product_productPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Product_productPUT* Urevenue_share_Product_productPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString name

	, FString description

	, bool visible

	, FString /* JSON STRING */ tags

	, FString defaultRevenueShareRulesetId

	, FString dataCaptureProjectId
)
{
	Urevenue_share_Product_productPUT* Proxy = NewObject<Urevenue_share_Product_productPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_name = name;

	Proxy->Field_description = description;

	Proxy->Field_visible = visible;

	Proxy->Field_tags = tags;

	Proxy->Field_defaultRevenueShareRulesetId = defaultRevenueShareRulesetId;

	Proxy->Field_dataCaptureProjectId = dataCaptureProjectId;


	return Proxy;
}

void Urevenue_share_Product_productPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /product put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/product?name=%s&description=%s&visible=%s&tags=%s&defaultRevenueShareRulesetId=%s&dataCaptureProjectId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, *FGenericPlatformHttp::UrlEncode(this->Field_description)

		, *FGenericPlatformHttp::UrlEncode(this->Field_visible ? TEXT("true") : TEXT("false"))

		, *FGenericPlatformHttp::UrlEncode(this->Field_tags)

		, *FGenericPlatformHttp::UrlEncode(this->Field_defaultRevenueShareRulesetId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_dataCaptureProjectId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Product_productPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /product put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Product(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /product put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Product_productPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Product_productPOST::Urevenue_share_Product_productPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Product_productPOST* Urevenue_share_Product_productPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString name

	, FString description

	, bool visible

	, FString /* JSON STRING */ tags

	, FString defaultRevenueShareRulesetId

	, FString dataCaptureProjectId
)
{
	Urevenue_share_Product_productPOST* Proxy = NewObject<Urevenue_share_Product_productPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_name = name;

	Proxy->Field_description = description;

	Proxy->Field_visible = visible;

	Proxy->Field_tags = tags;

	Proxy->Field_defaultRevenueShareRulesetId = defaultRevenueShareRulesetId;

	Proxy->Field_dataCaptureProjectId = dataCaptureProjectId;


	return Proxy;
}

void Urevenue_share_Product_productPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /product post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/product?id=%s&name=%s&description=%s&visible=%s&tags=%s&defaultRevenueShareRulesetId=%s&dataCaptureProjectId=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, *FGenericPlatformHttp::UrlEncode(this->Field_description)

		, *FGenericPlatformHttp::UrlEncode(this->Field_visible ? TEXT("true") : TEXT("false"))

		, *FGenericPlatformHttp::UrlEncode(this->Field_tags)

		, *FGenericPlatformHttp::UrlEncode(this->Field_defaultRevenueShareRulesetId)

		, *FGenericPlatformHttp::UrlEncode(this->Field_dataCaptureProjectId)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Product_productPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /product post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Product(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /product post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /product post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Product(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Product_productPOST>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Recipient_recipientsGET::Urevenue_share_Recipient_recipientsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Recipient_recipientsGET* Urevenue_share_Recipient_recipientsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit

	, bool showHidden
)
{
	Urevenue_share_Recipient_recipientsGET* Proxy = NewObject<Urevenue_share_Recipient_recipientsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;

	Proxy->Field_showHidden = showHidden;


	return Proxy;
}

void Urevenue_share_Recipient_recipientsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /recipients get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/recipients?start=%s&limit=%i&showHidden=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		, *FGenericPlatformHttp::UrlEncode(this->Field_showHidden ? TEXT("true") : TEXT("false"))

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Recipient_recipientsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedRecipients(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /recipients get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedRecipients(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedRecipients(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedRecipients(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_PaginatedRecipients(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /recipients get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedRecipients(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Recipient_recipientsGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Recipient_recipientsSearchGET::Urevenue_share_Recipient_recipientsSearchGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Recipient_recipientsSearchGET* Urevenue_share_Recipient_recipientsSearchGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString text
)
{
	Urevenue_share_Recipient_recipientsSearchGET* Proxy = NewObject<Urevenue_share_Recipient_recipientsSearchGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_text = text;


	return Proxy;
}

void Urevenue_share_Recipient_recipientsSearchGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /recipients/search get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/recipients/search?text=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_text)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Recipient_recipientsSearchGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients/search get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients/search get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientSearchResult>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /recipients/search get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients/search get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientSearchResult>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientSearchResult>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientSearchResult>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiverevenue_share_RecipientSearchResult> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiverevenue_share_RecipientSearchResult(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /recipients/search get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipients/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RecipientSearchResult>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Recipient_recipientsSearchGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Recipient_recipientGET::Urevenue_share_Recipient_recipientGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Recipient_recipientGET* Urevenue_share_Recipient_recipientGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Urevenue_share_Recipient_recipientGET* Proxy = NewObject<Urevenue_share_Recipient_recipientGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Urevenue_share_Recipient_recipientGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /recipient get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/recipient?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Recipient_recipientGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /recipient get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Recipient(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /recipient get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Recipient_recipientGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Recipient_recipientPUT::Urevenue_share_Recipient_recipientPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Recipient_recipientPUT* Urevenue_share_Recipient_recipientPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString name

	, FString description

	, int32 postDistributionTaxPercentage

	, int32 startingBalance

	, bool trackBalanceAndPayments

	, bool visible
)
{
	Urevenue_share_Recipient_recipientPUT* Proxy = NewObject<Urevenue_share_Recipient_recipientPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_name = name;

	Proxy->Field_description = description;

	Proxy->Field_postDistributionTaxPercentage = postDistributionTaxPercentage;

	Proxy->Field_startingBalance = startingBalance;

	Proxy->Field_trackBalanceAndPayments = trackBalanceAndPayments;

	Proxy->Field_visible = visible;


	return Proxy;
}

void Urevenue_share_Recipient_recipientPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /recipient put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/recipient?name=%s&description=%s&postDistributionTaxPercentage=%i&startingBalance=%i&trackBalanceAndPayments=%s&visible=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, *FGenericPlatformHttp::UrlEncode(this->Field_description)

		, this->Field_postDistributionTaxPercentage

		, this->Field_startingBalance

		, *FGenericPlatformHttp::UrlEncode(this->Field_trackBalanceAndPayments ? TEXT("true") : TEXT("false"))

		, *FGenericPlatformHttp::UrlEncode(this->Field_visible ? TEXT("true") : TEXT("false"))

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Recipient_recipientPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /recipient put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Recipient(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /recipient put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Recipient_recipientPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_Recipient_recipientPOST::Urevenue_share_Recipient_recipientPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_Recipient_recipientPOST* Urevenue_share_Recipient_recipientPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString name

	, FString description

	, int32 postDistributionTaxPercentage

	, int32 startingBalance

	, bool trackBalanceAndPayments

	, bool visible
)
{
	Urevenue_share_Recipient_recipientPOST* Proxy = NewObject<Urevenue_share_Recipient_recipientPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_name = name;

	Proxy->Field_description = description;

	Proxy->Field_postDistributionTaxPercentage = postDistributionTaxPercentage;

	Proxy->Field_startingBalance = startingBalance;

	Proxy->Field_trackBalanceAndPayments = trackBalanceAndPayments;

	Proxy->Field_visible = visible;


	return Proxy;
}

void Urevenue_share_Recipient_recipientPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /recipient post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/recipient?id=%s&name=%s&description=%s&postDistributionTaxPercentage=%i&startingBalance=%i&trackBalanceAndPayments=%s&visible=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, *FGenericPlatformHttp::UrlEncode(this->Field_description)

		, this->Field_postDistributionTaxPercentage

		, this->Field_startingBalance

		, *FGenericPlatformHttp::UrlEncode(this->Field_trackBalanceAndPayments ? TEXT("true") : TEXT("false"))

		, *FGenericPlatformHttp::UrlEncode(this->Field_visible ? TEXT("true") : TEXT("false"))

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_Recipient_recipientPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /recipient post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_Recipient(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /recipient post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /recipient post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_Recipient(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_Recipient_recipientPOST>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_RevenueShareRuleset_rulesetsGET::Urevenue_share_RevenueShareRuleset_rulesetsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_RevenueShareRuleset_rulesetsGET* Urevenue_share_RevenueShareRuleset_rulesetsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit

	, bool showHidden
)
{
	Urevenue_share_RevenueShareRuleset_rulesetsGET* Proxy = NewObject<Urevenue_share_RevenueShareRuleset_rulesetsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;

	Proxy->Field_showHidden = showHidden;


	return Proxy;
}

void Urevenue_share_RevenueShareRuleset_rulesetsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /rulesets get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/rulesets?start=%s&limit=%i&showHidden=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		, *FGenericPlatformHttp::UrlEncode(this->Field_showHidden ? TEXT("true") : TEXT("false"))

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedRevenueShareRulesets(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /rulesets get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_PaginatedRevenueShareRulesets(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedRevenueShareRulesets(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedRevenueShareRulesets(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_PaginatedRevenueShareRulesets(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /rulesets get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_PaginatedRevenueShareRulesets(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetsGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_RevenueShareRuleset_rulesetsSearchGET::Urevenue_share_RevenueShareRuleset_rulesetsSearchGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_RevenueShareRuleset_rulesetsSearchGET* Urevenue_share_RevenueShareRuleset_rulesetsSearchGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString text
)
{
	Urevenue_share_RevenueShareRuleset_rulesetsSearchGET* Proxy = NewObject<Urevenue_share_RevenueShareRuleset_rulesetsSearchGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_text = text;


	return Proxy;
}

void Urevenue_share_RevenueShareRuleset_rulesetsSearchGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /rulesets/search get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/rulesets/search?text=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_text)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetsSearchGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets/search get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets/search get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_RevenueShareRulesetSearchResult>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /rulesets/search get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets/search get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_RevenueShareRulesetSearchResult>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RevenueShareRulesetSearchResult>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RevenueShareRulesetSearchResult>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiverevenue_share_RevenueShareRulesetSearchResult> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiverevenue_share_RevenueShareRulesetSearchResult(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /rulesets/search get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /rulesets/search get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_RevenueShareRulesetSearchResult>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetsSearchGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_RevenueShareRuleset_rulesetGET::Urevenue_share_RevenueShareRuleset_rulesetGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_RevenueShareRuleset_rulesetGET* Urevenue_share_RevenueShareRuleset_rulesetGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Urevenue_share_RevenueShareRuleset_rulesetGET* Proxy = NewObject<Urevenue_share_RevenueShareRuleset_rulesetGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Urevenue_share_RevenueShareRuleset_rulesetGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /ruleset get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/ruleset?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /ruleset get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_RevenueShareRuleset(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /ruleset get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetGET>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_RevenueShareRuleset_rulesetPUT::Urevenue_share_RevenueShareRuleset_rulesetPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_RevenueShareRuleset_rulesetPUT* Urevenue_share_RevenueShareRuleset_rulesetPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString name

	, FString description

	, TArray<FHiverevenue_share_RevenueShareRulesetRule> ruleset

	, bool visible
)
{
	Urevenue_share_RevenueShareRuleset_rulesetPUT* Proxy = NewObject<Urevenue_share_RevenueShareRuleset_rulesetPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_name = name;

	Proxy->Field_description = description;

	Proxy->Field_ruleset = TArray<FHiverevenue_share_RevenueShareRulesetRule>(ruleset);

	Proxy->Field_visible = visible;


	return Proxy;
}

void Urevenue_share_RevenueShareRuleset_rulesetPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /ruleset put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/ruleset?name=%s&description=%s&visible=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, *FGenericPlatformHttp::UrlEncode(this->Field_description)

		, *FGenericPlatformHttp::UrlEncode(this->Field_visible ? TEXT("true") : TEXT("false"))

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /ruleset put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_RevenueShareRuleset(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /ruleset put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetPUT>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_RevenueShareRuleset_rulesetPOST::Urevenue_share_RevenueShareRuleset_rulesetPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_RevenueShareRuleset_rulesetPOST* Urevenue_share_RevenueShareRuleset_rulesetPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id

	, FString name

	, FString description

	, TArray<FHiverevenue_share_RevenueShareRulesetRule> ruleset

	, bool visible
)
{
	Urevenue_share_RevenueShareRuleset_rulesetPOST* Proxy = NewObject<Urevenue_share_RevenueShareRuleset_rulesetPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;

	Proxy->Field_name = name;

	Proxy->Field_description = description;

	Proxy->Field_ruleset = TArray<FHiverevenue_share_RevenueShareRulesetRule>(ruleset);

	Proxy->Field_visible = visible;


	return Proxy;
}

void Urevenue_share_RevenueShareRuleset_rulesetPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /ruleset post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/ruleset?id=%s&name=%s&description=%s&visible=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		, *FGenericPlatformHttp::UrlEncode(this->Field_name)

		, *FGenericPlatformHttp::UrlEncode(this->Field_description)

		, *FGenericPlatformHttp::UrlEncode(this->Field_visible ? TEXT("true") : TEXT("false"))

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /ruleset post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiverevenue_share_RevenueShareRuleset(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /ruleset post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiverevenue_share_RevenueShareRuleset(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetPOST>(this));
	HttpRequest->ProcessRequest();
}



Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT::Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT* Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString productId

	, float amount

	, FString currency

	, float sourceAmount

	, FString sourceCurrency

	, TArray<FHiverevenue_share_RevenueShareRulesetRule> rulesetJson
)
{
	Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT* Proxy = NewObject<Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_productId = productId;

	Proxy->Field_amount = amount;

	Proxy->Field_currency = currency;

	Proxy->Field_sourceAmount = sourceAmount;

	Proxy->Field_sourceCurrency = sourceCurrency;

	Proxy->Field_rulesetJson = TArray<FHiverevenue_share_RevenueShareRulesetRule>(rulesetJson);


	return Proxy;
}

void Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] revenue-share /ruleset/simulate put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://revenue-share-api.hivemp.com/v1/ruleset/simulate?productId=%s&amount=%f&currency=%s&sourceAmount=%f&sourceCurrency=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_productId)

		, this->Field_amount

		, *FGenericPlatformHttp::UrlEncode(this->Field_currency)

		, this->Field_sourceAmount

		, *FGenericPlatformHttp::UrlEncode(this->Field_sourceCurrency)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset/simulate put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset/simulate put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_SimulatedPayment>(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] revenue-share /ruleset/simulate put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset/simulate put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( TArray<FHiverevenue_share_SimulatedPayment>(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset/simulate put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_SimulatedPayment>(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset/simulate put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_SimulatedPayment>(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TArray<TSharedPtr<FJsonValue>>* JsonArray;
			if (JsonValue->TryGetArray(JsonArray))
			{
				TArray<FHiverevenue_share_SimulatedPayment> Result;
				for (int i = 0; i < JsonArray->Num(); i++)
				{
					const TSharedPtr<FJsonObject>* JsonArrayObj;
					if ((*JsonArray)[i]->TryGetObject(JsonArrayObj))
					{
						Result.Add(DeserializeFHiverevenue_share_SimulatedPayment(*JsonArrayObj));
					}

				}
				UE_LOG_HIVE(Warning, TEXT("[success] revenue-share /ruleset/simulate put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] revenue-share /ruleset/simulate put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( TArray<FHiverevenue_share_SimulatedPayment>(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT>(this));
	HttpRequest->ProcessRequest();
}



struct FHivetemp_session_TempSession DeserializeFHivetemp_session_TempSession(const TSharedPtr<FJsonObject> obj)
{
	struct FHivetemp_session_TempSession Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	double F_expiry;
	if (obj->TryGetNumberField(TEXT("expiry"), F_expiry))
	{
		Target.expiry = (int32)F_expiry;
	}

	double F_start;
	if (obj->TryGetNumberField(TEXT("start"), F_start))
	{
		Target.start = (int32)F_start;
	}

	double F_billedMinutes;
	if (obj->TryGetNumberField(TEXT("billedMinutes"), F_billedMinutes))
	{
		Target.billedMinutes = (int32)F_billedMinutes;
	}


	return Target;
}



struct FHivetemp_session_TempSessionWithSecrets DeserializeFHivetemp_session_TempSessionWithSecrets(const TSharedPtr<FJsonObject> obj)
{
	struct FHivetemp_session_TempSessionWithSecrets Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	double F_expiry;
	if (obj->TryGetNumberField(TEXT("expiry"), F_expiry))
	{
		Target.expiry = (int32)F_expiry;
	}

	double F_start;
	if (obj->TryGetNumberField(TEXT("start"), F_start))
	{
		Target.start = (int32)F_start;
	}

	double F_billedMinutes;
	if (obj->TryGetNumberField(TEXT("billedMinutes"), F_billedMinutes))
	{
		Target.billedMinutes = (int32)F_billedMinutes;
	}

	FString F_apiKey;
	if (obj->TryGetStringField(TEXT("apiKey"), F_apiKey))
	{
		Target.apiKey = F_apiKey;
	}

	FString F_secretKey;
	if (obj->TryGetStringField(TEXT("secretKey"), F_secretKey))
	{
		Target.secretKey = F_secretKey;
	}


	return Target;
}



struct FHivetemp_session_PaginatedTempSessions DeserializeFHivetemp_session_PaginatedTempSessions(const TSharedPtr<FJsonObject> obj)
{
	struct FHivetemp_session_PaginatedTempSessions Target;
	

	FString F_next;
	if (obj->TryGetStringField(TEXT("next"), F_next))
	{
		Target.next = F_next;
	}

	bool F_moreResults;
	if (obj->TryGetBoolField(TEXT("moreResults"), F_moreResults))
	{
		Target.moreResults = (bool)F_moreResults;
	}

	const TArray<TSharedPtr<FJsonValue>>* F_results;
	if (obj->TryGetArrayField(TEXT("results"), F_results))
	{
		for (int i = 0; i < F_results->Num(); i++)
		{

			const TSharedPtr<FJsonObject>* A_results;
			if ((*F_results)[i]->TryGetObject(A_results))
			{
				Target.results.Add(DeserializeFHivetemp_session_TempSession(*A_results));
			}

		}
	}


	return Target;
}



Utemp_session_TemporarySession_sessionGET::Utemp_session_TemporarySession_sessionGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Utemp_session_TemporarySession_sessionGET* Utemp_session_TemporarySession_sessionGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Utemp_session_TemporarySession_sessionGET* Proxy = NewObject<Utemp_session_TemporarySession_sessionGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Utemp_session_TemporarySession_sessionGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] temp-session /session get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://temp-session-api.hivemp.com/v1/session?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Utemp_session_TemporarySession_sessionGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] temp-session /session get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivetemp_session_TempSession(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] temp-session /session get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Utemp_session_TemporarySession_sessionGET>(this));
	HttpRequest->ProcessRequest();
}



Utemp_session_TemporarySession_sessionPUT::Utemp_session_TemporarySession_sessionPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Utemp_session_TemporarySession_sessionPUT* Utemp_session_TemporarySession_sessionPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey
)
{
	Utemp_session_TemporarySession_sessionPUT* Proxy = NewObject<Utemp_session_TemporarySession_sessionPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	

	return Proxy;
}

void Utemp_session_TemporarySession_sessionPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] temp-session /session put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://temp-session-api.hivemp.com/v1/session?")

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Utemp_session_TemporarySession_sessionPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivetemp_session_TempSessionWithSecrets(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] temp-session /session put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivetemp_session_TempSessionWithSecrets(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSessionWithSecrets(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSessionWithSecrets(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivetemp_session_TempSessionWithSecrets(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] temp-session /session put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSessionWithSecrets(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Utemp_session_TemporarySession_sessionPUT>(this));
	HttpRequest->ProcessRequest();
}



Utemp_session_TemporarySession_sessionPOST::Utemp_session_TemporarySession_sessionPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Utemp_session_TemporarySession_sessionPOST* Utemp_session_TemporarySession_sessionPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Utemp_session_TemporarySession_sessionPOST* Proxy = NewObject<Utemp_session_TemporarySession_sessionPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Utemp_session_TemporarySession_sessionPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] temp-session /session post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://temp-session-api.hivemp.com/v1/session?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Utemp_session_TemporarySession_sessionPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] temp-session /session post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivetemp_session_TempSession(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] temp-session /session post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_TempSession(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Utemp_session_TemporarySession_sessionPOST>(this));
	HttpRequest->ProcessRequest();
}



Utemp_session_TemporarySession_sessionDELETE::Utemp_session_TemporarySession_sessionDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Utemp_session_TemporarySession_sessionDELETE* Utemp_session_TemporarySession_sessionDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Utemp_session_TemporarySession_sessionDELETE* Proxy = NewObject<Utemp_session_TemporarySession_sessionDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Utemp_session_TemporarySession_sessionDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] temp-session /session delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://temp-session-api.hivemp.com/v1/session?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Utemp_session_TemporarySession_sessionDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] temp-session /session delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] temp-session /session delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] temp-session /session delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] temp-session /session delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Utemp_session_TemporarySession_sessionDELETE>(this));
	HttpRequest->ProcessRequest();
}



Utemp_session_TemporarySessionAdmin_sessionsGET::Utemp_session_TemporarySessionAdmin_sessionsGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Utemp_session_TemporarySessionAdmin_sessionsGET* Utemp_session_TemporarySessionAdmin_sessionsGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString start

	, int32 limit
)
{
	Utemp_session_TemporarySessionAdmin_sessionsGET* Proxy = NewObject<Utemp_session_TemporarySessionAdmin_sessionsGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_start = start;

	Proxy->Field_limit = limit;


	return Proxy;
}

void Utemp_session_TemporarySessionAdmin_sessionsGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] temp-session /sessions get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://temp-session-api.hivemp.com/v1/sessions?start=%s&limit=%i")

		, *FGenericPlatformHttp::UrlEncode(this->Field_start)

		, this->Field_limit

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Utemp_session_TemporarySessionAdmin_sessionsGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /sessions get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /sessions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivetemp_session_PaginatedTempSessions(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] temp-session /sessions get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] temp-session /sessions get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHivetemp_session_PaginatedTempSessions(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /sessions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_PaginatedTempSessions(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /sessions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_PaginatedTempSessions(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHivetemp_session_PaginatedTempSessions(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] temp-session /sessions get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] temp-session /sessions get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHivetemp_session_PaginatedTempSessions(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Utemp_session_TemporarySessionAdmin_sessionsGET>(this));
	HttpRequest->ProcessRequest();
}



struct FHiveugc_cache_UGCCacheItem DeserializeFHiveugc_cache_UGCCacheItem(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveugc_cache_UGCCacheItem Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_lookupKey;
	if (obj->TryGetStringField(TEXT("lookupKey"), F_lookupKey))
	{
		Target.lookupKey = F_lookupKey;
	}

	FString F_owner;
	if (obj->TryGetStringField(TEXT("owner"), F_owner))
	{
		Target.owner = F_owner;
	}


	return Target;
}



Uugc_cache_UGCCache_itemPUT::Uugc_cache_UGCCache_itemPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uugc_cache_UGCCache_itemPUT* Uugc_cache_UGCCache_itemPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString lookupKey

	, TArray<uint8> content
)
{
	Uugc_cache_UGCCache_itemPUT* Proxy = NewObject<Uugc_cache_UGCCache_itemPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_lookupKey = lookupKey;

	Proxy->Field_content = TArray<uint8>(content);


	return Proxy;
}

void Uugc_cache_UGCCache_itemPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] ugc-cache /item put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://ugc-cache-api.hivemp.com/v1/item?lookupKey=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_lookupKey)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uugc_cache_UGCCache_itemPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /item put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /item put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveugc_cache_UGCCacheItem(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] ugc-cache /item put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /item put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveugc_cache_UGCCacheItem(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /item put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveugc_cache_UGCCacheItem(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /item put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveugc_cache_UGCCacheItem(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveugc_cache_UGCCacheItem(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] ugc-cache /item put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /item put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveugc_cache_UGCCacheItem(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uugc_cache_UGCCache_itemPUT>(this));
	HttpRequest->ProcessRequest();
}



Uugc_cache_UGCCache_contentGET::Uugc_cache_UGCCache_contentGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uugc_cache_UGCCache_contentGET* Uugc_cache_UGCCache_contentGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString lookupKey
)
{
	Uugc_cache_UGCCache_contentGET* Proxy = NewObject<Uugc_cache_UGCCache_contentGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_lookupKey = lookupKey;


	return Proxy;
}

void Uugc_cache_UGCCache_contentGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] ugc-cache /content get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://ugc-cache-api.hivemp.com/v1/content?lookupKey=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_lookupKey)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uugc_cache_UGCCache_contentGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /content get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /content get: %s"), *(ResultError.Message));
			OnFailure.Broadcast(ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] ugc-cache /content get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /content get: %s"), *(ResultError.Message));
			OnFailure.Broadcast(ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /content get: %s"), *(ResultError.Message));
				OnFailure.Broadcast(ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] ugc-cache /content get: %s"), *(ResultError.Message));
				OnFailure.Broadcast(ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			UE_LOG_HIVE(Warning, TEXT("[success] ugc-cache /content get"));
			OnSuccess.Broadcast(ResultError);
		
		}
	}, TWeakObjectPtr<Uugc_cache_UGCCache_contentGET>(this));
	HttpRequest->ProcessRequest();
}



struct FHiveuser_session_UserSession DeserializeFHiveuser_session_UserSession(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveuser_session_UserSession Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_accountId;
	if (obj->TryGetStringField(TEXT("accountId"), F_accountId))
	{
		Target.accountId = F_accountId;
	}

	double F_expiry;
	if (obj->TryGetNumberField(TEXT("expiry"), F_expiry))
	{
		Target.expiry = (int32)F_expiry;
	}

	double F_start;
	if (obj->TryGetNumberField(TEXT("start"), F_start))
	{
		Target.start = (int32)F_start;
	}

	double F_billedMinutes;
	if (obj->TryGetNumberField(TEXT("billedMinutes"), F_billedMinutes))
	{
		Target.billedMinutes = (int32)F_billedMinutes;
	}


	return Target;
}



struct FHiveuser_session_UserSessionWithSecrets DeserializeFHiveuser_session_UserSessionWithSecrets(const TSharedPtr<FJsonObject> obj)
{
	struct FHiveuser_session_UserSessionWithSecrets Target;
	

	FString F_id;
	if (obj->TryGetStringField(TEXT("id"), F_id))
	{
		Target.id = F_id;
	}

	FString F_accountId;
	if (obj->TryGetStringField(TEXT("accountId"), F_accountId))
	{
		Target.accountId = F_accountId;
	}

	double F_expiry;
	if (obj->TryGetNumberField(TEXT("expiry"), F_expiry))
	{
		Target.expiry = (int32)F_expiry;
	}

	double F_start;
	if (obj->TryGetNumberField(TEXT("start"), F_start))
	{
		Target.start = (int32)F_start;
	}

	double F_billedMinutes;
	if (obj->TryGetNumberField(TEXT("billedMinutes"), F_billedMinutes))
	{
		Target.billedMinutes = (int32)F_billedMinutes;
	}

	FString F_apiKey;
	if (obj->TryGetStringField(TEXT("apiKey"), F_apiKey))
	{
		Target.apiKey = F_apiKey;
	}

	FString F_secretKey;
	if (obj->TryGetStringField(TEXT("secretKey"), F_secretKey))
	{
		Target.secretKey = F_secretKey;
	}


	return Target;
}



Uuser_session_UserSession_sessionGET::Uuser_session_UserSession_sessionGET(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uuser_session_UserSession_sessionGET* Uuser_session_UserSession_sessionGET::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uuser_session_UserSession_sessionGET* Proxy = NewObject<Uuser_session_UserSession_sessionGET>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uuser_session_UserSession_sessionGET::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] user-session /session get"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://user-session-api.hivemp.com/v1/session?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("get"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uuser_session_UserSession_sessionGET> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session get: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] user-session /session get: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session get: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveuser_session_UserSession(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] user-session /session get"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session get: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uuser_session_UserSession_sessionGET>(this));
	HttpRequest->ProcessRequest();
}



Uuser_session_UserSession_sessionPUT::Uuser_session_UserSession_sessionPUT(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uuser_session_UserSession_sessionPUT* Uuser_session_UserSession_sessionPUT::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString authenticationProvider

	, FString credentials
)
{
	Uuser_session_UserSession_sessionPUT* Proxy = NewObject<Uuser_session_UserSession_sessionPUT>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_authenticationProvider = authenticationProvider;

	Proxy->Field_credentials = credentials;


	return Proxy;
}

void Uuser_session_UserSession_sessionPUT::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] user-session /session put"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://user-session-api.hivemp.com/v1/session?authenticationProvider=%s&credentials=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_authenticationProvider)

		, *FGenericPlatformHttp::UrlEncode(this->Field_credentials)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("put"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uuser_session_UserSession_sessionPUT> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session put: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveuser_session_UserSessionWithSecrets(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] user-session /session put: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session put: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveuser_session_UserSessionWithSecrets(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSessionWithSecrets(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSessionWithSecrets(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveuser_session_UserSessionWithSecrets(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] user-session /session put"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session put: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSessionWithSecrets(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uuser_session_UserSession_sessionPUT>(this));
	HttpRequest->ProcessRequest();
}



Uuser_session_UserSession_sessionPOST::Uuser_session_UserSession_sessionPOST(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uuser_session_UserSession_sessionPOST* Uuser_session_UserSession_sessionPOST::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uuser_session_UserSession_sessionPOST* Proxy = NewObject<Uuser_session_UserSession_sessionPOST>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uuser_session_UserSession_sessionPOST::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] user-session /session post"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://user-session-api.hivemp.com/v1/session?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("post"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uuser_session_UserSession_sessionPOST> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session post: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] user-session /session post: %s"), *(Response->GetContentAsString()));

		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session post: %s"), *(ResultError.Message));
			OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				auto Result = DeserializeFHiveuser_session_UserSession(*JsonObject);
				UE_LOG_HIVE(Warning, TEXT("[success] user-session /session post"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session post: %s"), *(ResultError.Message));
				OnFailure.Broadcast( FHiveuser_session_UserSession(), ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uuser_session_UserSession_sessionPOST>(this));
	HttpRequest->ProcessRequest();
}



Uuser_session_UserSession_sessionDELETE::Uuser_session_UserSession_sessionDELETE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr) { }

Uuser_session_UserSession_sessionDELETE* Uuser_session_UserSession_sessionDELETE::PerformHiveCall(
	UObject* WorldContextObject,
	FString ApiKey

	, FString id
)
{
	Uuser_session_UserSession_sessionDELETE* Proxy = NewObject<Uuser_session_UserSession_sessionDELETE>();

	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ApiKey = ApiKey;

	
	Proxy->Field_id = id;


	return Proxy;
}

void Uuser_session_UserSession_sessionDELETE::Activate()
{
	UE_LOG_HIVE(Display, TEXT("[start] user-session /session delete"));


	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(FString::Printf(
		TEXT("https://user-session-api.hivemp.com/v1/session?id=%s")

		, *FGenericPlatformHttp::UrlEncode(this->Field_id)

		
		));
	HttpRequest->SetHeader(TEXT("api_key"), this->ApiKey);
	HttpRequest->SetVerb(TEXT("delete"));
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TWeakObjectPtr<Uuser_session_UserSession_sessionDELETE> SelfRef)
	{
		if (!SelfRef.IsValid())
		{
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session delete: Callback proxy is invalid (did the game shutdown?)"));
			return;
		}

		if (!HttpResponse.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = 0;
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("HTTP response was not valid!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}

		auto Response = HttpResponse.Get();

		UE_LOG_HIVE(Warning, TEXT("[info] user-session /session delete: %s"), *(Response->GetContentAsString()));

		
		if (Response->GetContentAsString().Equals(TEXT("true")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] user-session /session delete"));
			OnSuccess.Broadcast(true, ResultError);
		}
		else if (Response->GetContentAsString().Equals(TEXT("false")))
		{
			struct FHiveApiError ResultError;
			UE_LOG_HIVE(Warning, TEXT("[success] user-session /session delete"));
			OnSuccess.Broadcast(false, ResultError);
		}
		

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		{
			struct FHiveApiError ResultError;
			ResultError.HttpStatusCode = Response->GetResponseCode();
			ResultError.ErrorCode = 0;
			ResultError.Message = TEXT("Unable to deserialize JSON response!");
			ResultError.Parameter = TEXT("");
			UE_LOG_HIVE(Error, TEXT("[fail] user-session /session delete: %s"), *(ResultError.Message));
			OnFailure.Broadcast( 0, ResultError);
			return;
		}
		
		if (!bSucceeded || HttpResponse->GetResponseCode() != 200)
		{
			const TSharedPtr<FJsonObject>* JsonObject;
			if (JsonValue->TryGetObject(JsonObject))
			{
				// Parse as Hive system error.
				FString Message, Parameter;
				double ErrorCode;
				auto GotMessage = (*JsonObject)->TryGetStringField(TEXT("message"), Message);
				auto GotParameter = (*JsonObject)->TryGetStringField(TEXT("fields"), Parameter);
				auto GotErrorCode = (*JsonObject)->TryGetNumberField(TEXT("code"), ErrorCode);

				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				if (GotErrorCode)
				{
					ResultError.ErrorCode = (int32)ErrorCode;
				}
				if (GotMessage)
				{
					ResultError.Message = Message;
				}
				if (GotParameter)
				{
					ResultError.Parameter = Parameter;
				}
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
			else
			{
				struct FHiveApiError ResultError;
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as Hive system error!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		}

		{
			struct FHiveApiError ResultError;

		
			bool Result;
			if (JsonValue->TryGetBool(Result))
			{
				UE_LOG_HIVE(Warning, TEXT("[success] user-session /session delete"));
				OnSuccess.Broadcast(Result, ResultError);
			}
			else
			{
				ResultError.HttpStatusCode = Response->GetResponseCode();
				ResultError.ErrorCode = 0;
				ResultError.Message = TEXT("Unable to deserialize JSON response as expected type!");
				ResultError.Parameter = TEXT("");
				UE_LOG_HIVE(Error, TEXT("[fail] user-session /session delete: %s"), *(ResultError.Message));
				OnFailure.Broadcast( 0, ResultError);
				return;
			}
		
		}
	}, TWeakObjectPtr<Uuser_session_UserSession_sessionDELETE>(this));
	HttpRequest->ProcessRequest();
}



