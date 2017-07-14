









#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DelegateCombinations.h"
#include "OnlineSubsystem.h"
#include "JsonReader.h"
#include "JsonSerializer.h"
#include "IHttpResponse.h"
#include "GenericPlatformHttp.h"
#include "Base64.h"
#include "HiveBlueprintLibrary.generated.h"

#define UE_LOG_HIVE(Verbosity, Format, ...) \
{ \
	UE_LOG(LogOnline, Verbosity, TEXT("%s%s"), TEXT("HiveMP: "), *FString::Printf(Format, ##__VA_ARGS__)); \
}

USTRUCT(BlueprintType)
struct FHiveApiError
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 HttpStatusCode;

	UPROPERTY(BlueprintReadOnly)
	int32 ErrorCode;

	UPROPERTY(BlueprintReadOnly)
	FString Message;

	UPROPERTY(BlueprintReadOnly)
	FString Parameter;
};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Administrative Sessions AdminSession"))
struct FHiveadmin_session_AdminSession
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString username;

	UPROPERTY(BlueprintReadOnly)
	int32 expiry;

	UPROPERTY(BlueprintReadOnly)
	FString project;

};


struct FHiveadmin_session_AdminSession DeserializeFHiveadmin_session_AdminSession(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Administrative Sessions AdminSessionWithSecrets"))
struct FHiveadmin_session_AdminSessionWithSecrets
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString username;

	UPROPERTY(BlueprintReadOnly)
	int32 expiry;

	UPROPERTY(BlueprintReadOnly)
	FString project;

	UPROPERTY(BlueprintReadOnly)
	FString apiKey;

	UPROPERTY(BlueprintReadOnly)
	FString secretKey;

};


struct FHiveadmin_session_AdminSessionWithSecrets DeserializeFHiveadmin_session_AdminSessionWithSecrets(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Administrative Sessions AdminUserSummary"))
struct FHiveadmin_session_AdminUserSummary
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString username;

};


struct FHiveadmin_session_AdminUserSummary DeserializeFHiveadmin_session_AdminUserSummary(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Administrative Sessions Project"))
struct FHiveadmin_session_Project
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString name;

	UPROPERTY(BlueprintReadOnly)
	bool active;

};


struct FHiveadmin_session_Project DeserializeFHiveadmin_session_Project(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Administrative Sessions ProjectAccessEntry"))
struct FHiveadmin_session_ProjectAccessEntry
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString type;

	UPROPERTY(BlueprintReadOnly)
	FString username;

	UPROPERTY(BlueprintReadOnly)
	FString projectId;

	UPROPERTY(BlueprintReadOnly)
	FString projectName;

};


struct FHiveadmin_session_ProjectAccessEntry DeserializeFHiveadmin_session_ProjectAccessEntry(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_AdministrationSession_sessionGET_Delegate, const FHiveadmin_session_AdminSession, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_AdministrationSession_sessionGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_sessionGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_sessionGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves details about an existing administrative session", ToolTip="Retrieves information about an existing administrative session, based on the session identifier.\nThis call returns the session identifier and the expiry time of the session based on a UNIX\ntimestamp in the UTC timezone."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_AdministrationSession_sessionGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_AdministrationSession_sessionPUT_Delegate, const FHiveadmin_session_AdminSessionWithSecrets, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_AdministrationSession_sessionPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_sessionPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_sessionPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new administrative session", ToolTip="Administrative sessions have access to administer the Hive projects that they are associated with.\nThere is no billing cost associated with administrative sessions.\n\nThis API is rate-limited by IP address."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_AdministrationSession_sessionPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString username

		, FString password

		, FString project
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_username;

	FString Field_password;

	FString Field_project;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_AdministrationSession_sessionPOST_Delegate, const FHiveadmin_session_AdminSession, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_AdministrationSession_sessionPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_sessionPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_sessionPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Extend the expiry of your current administrative session", ToolTip="Extends the expiry of your current administrative session to the current time, plus one hour.  You should reset the\nexpiry of a session after 30 minutes to ensure that you allow a reasonable window in case the\noperation encounters an error."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_AdministrationSession_sessionPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_AdministrationSession_sessionDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_AdministrationSession_sessionDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_sessionDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_sessionDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Explicitly delete an administrative session", ToolTip="Explicitly deletes an administrative session based on it's identifier."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_AdministrationSession_sessionDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_AdministrationSession_switchPUT_Delegate, const FHiveadmin_session_AdminSessionWithSecrets, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_AdministrationSession_switchPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_switchPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationSession_switchPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new administrative session that targets the specified project", ToolTip="Each administrative session is issued for a specific project.  When you want to modify or query\nresources in a different project, you need to obtain a different session for that project.\n\nTo ensure that you do not need to provide the user's username and password again, this endpoint\nallows you to create a session for a project the user has access to, from a session in another\nproject."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_AdministrationSession_switchPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_AdministrationUser_userGET_Delegate, const FHiveadmin_session_AdminUserSummary, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_AdministrationUser_userGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationUser_userGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationUser_userGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves details about an administration user account", ToolTip="Administration user accounts manage projects within Hive, most often using the Hive Console.\nHowever, all of the operations the Hive console performs are available as APIs, so you can\nautomate any administrative operation in the system."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_AdministrationUser_userGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString username
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_username;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_AdministrationUser_userPUT_Delegate, const FHiveadmin_session_AdminUserSummary, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_AdministrationUser_userPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationUser_userPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationUser_userPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Requests the creation of a new administration user account", ToolTip="This initiates the workflow for the creation of a new administrative user account.  While\nthis creates attributes of the account, the account is unverified until the user confirms\ntheir account creation by clicking a link in an email that is sent to the designated email\naddress.  Unverified accounts cannot login and automatically expire after 5 days.\n\nThis API is rate-limited by IP address."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_AdministrationUser_userPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString username

		, FString password

		, FString email
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_username;

	FString Field_password;

	FString Field_email;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_AdministrationUser_verifyPOST_Delegate, const FHiveadmin_session_AdminUserSummary, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_AdministrationUser_verifyPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationUser_verifyPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_AdministrationUser_verifyPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Verifies an account using a code that the system provided in the email", ToolTip="This API is often automatically called by the Hive console, as the system by default links\nfrom account confirmation emails to the verification endpoint on the Hive console which in-turn\nuses this API.\n\nThis API is rate-limited by IP address."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_AdministrationUser_verifyPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString username

		, FString code
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_username;

	FString Field_code;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_projectsGET_Delegate, const TArray<FHiveadmin_session_Project>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_projectsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_projectsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_projectsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of projects that the user has access to", ToolTip="Retrieves a list of all the projects a user has access to."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_projectsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_projectGET_Delegate, const FHiveadmin_session_Project, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_projectGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_projectGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_projectGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves information about a specific project", ToolTip="Retrieves information about a specific project, if the user has access to see it."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_projectGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_projectPUT_Delegate, const FHiveadmin_session_Project, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_projectPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_projectPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_projectPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new project", ToolTip="Creates a new project with the given name."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_projectPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString name
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_name;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_projectPOST_Delegate, const FHiveadmin_session_Project, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_projectPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_projectPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_projectPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Renames a project, or toggles whether it is active or not", ToolTip="Renames a project and / or toggles whether or not it is active.  Session services will\nnot issue non-administrative sessions for inactive projects."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_projectPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString name

		, bool active
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_name;

	bool Field_active;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_accessGET_Delegate, const TArray<FHiveadmin_session_ProjectAccessEntry>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_accessGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of users that have access to the project", ToolTip="Retrieves a list of users that have access to the specific project.\nYour current session must belong to that project, so if needed, you'll need\nto call the `/switch` endpoint to obtain a session appropriate for querying\nthe user permissions for that project."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_accessGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_accessUserPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_accessUserPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessUserPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessUserPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Grant a user access to a specific project", ToolTip="Grant a user full read-write administrative access to a specified project.\nYour current session must belong to that project, so if needed, you'll need\nto call the `/switch` endpoint to obtain a session appropriate for modifying\nthe user list for that project."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_accessUserPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString username
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_username;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_accessUserDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_accessUserDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessUserDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessUserDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Revokes user access from a specific project", ToolTip=""), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_accessUserDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString username
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_username;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_accessProjectPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_accessProjectPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessProjectPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessProjectPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Grant all users of another project access to a specific project", ToolTip="Grant all users of another project full read-write administrative access to a specified project.\nYour current session must belong to that project, so if needed, you'll need\nto call the `/switch` endpoint to obtain a session appropriate for modifying\nthe user list for that project."), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_accessProjectPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString projectId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_projectId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fadmin_session_ProjectInfo_accessProjectDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uadmin_session_ProjectInfo_accessProjectDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessProjectDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fadmin_session_ProjectInfo_accessProjectDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Revokes project access from a specific project", ToolTip=""), Category="HiveMP|Administrative Sessions")
	static Uadmin_session_ProjectInfo_accessProjectDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString projectId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_projectId;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Attributes AttributeKey"))
struct FHiveattribute_AttributeKey
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString key;

	UPROPERTY(BlueprintReadOnly)
	FString ownerId;

};


struct FHiveattribute_AttributeKey DeserializeFHiveattribute_AttributeKey(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Attributes AttributeData"))
struct FHiveattribute_AttributeData
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString key;

	UPROPERTY(BlueprintReadOnly)
	FString ownerId;

	UPROPERTY(BlueprintReadOnly)
	FString value;

};


struct FHiveattribute_AttributeData DeserializeFHiveattribute_AttributeData(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fattribute_Attribute_attributesGET_Delegate, const TArray<FHiveattribute_AttributeKey>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uattribute_Attribute_attributesGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fattribute_Attribute_attributesGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fattribute_Attribute_attributesGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of attribute keys on an object", ToolTip="Retrieves a list of attribute keys on an object.  This method does NOT return\nthe attribute values."), Category="HiveMP|Attributes")
	static Uattribute_Attribute_attributesGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fattribute_Attribute_attributeGET_Delegate, const FHiveattribute_AttributeData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uattribute_Attribute_attributeGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fattribute_Attribute_attributeGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fattribute_Attribute_attributeGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves an attribute and it's value from an object", ToolTip="Retrieves exactly one attribute and it's value from an object."), Category="HiveMP|Attributes")
	static Uattribute_Attribute_attributeGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString key

		, FString ownerId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_key;

	FString Field_ownerId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fattribute_Attribute_attributePUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uattribute_Attribute_attributePUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fattribute_Attribute_attributePUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fattribute_Attribute_attributePUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets or updates an attribute on an object", ToolTip="Sets or updates an attribute on an object. The caller of this API\nwill be the owner of this attribute. There can be multiple attributes\nwith the same key, but with different owners."), Category="HiveMP|Attributes")
	static Uattribute_Attribute_attributePUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString key

		, FString value
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_key;

	FString Field_value;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fattribute_Attribute_attributeDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uattribute_Attribute_attributeDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fattribute_Attribute_attributeDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fattribute_Attribute_attributeDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Deletes an attribute from an object", ToolTip="Deletes the specified attribute if it exists."), Category="HiveMP|Attributes")
	static Uattribute_Attribute_attributeDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString key

		, FString ownerId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_key;

	FString Field_ownerId;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Events EventTypeVersion"))
struct FHiveevent_EventTypeVersion
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString eventType;

	UPROPERTY(BlueprintReadOnly)
	FString eventTypeVersion;

	UPROPERTY(BlueprintReadOnly)
	FString status;

	UPROPERTY(BlueprintReadOnly)
	FString statusDetailed;

	UPROPERTY(BlueprintReadOnly)
	FString /* JSON STRING */ schema;

};


struct FHiveevent_EventTypeVersion DeserializeFHiveevent_EventTypeVersion(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(Fevent_Event_eventInsertPUT_Delegate, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uevent_Event_eventInsertPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fevent_Event_eventInsertPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fevent_Event_eventInsertPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Inserts a single event with the specified event type and version", ToolTip=""), Category="HiveMP|Events")
	static Uevent_Event_eventInsertPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString eventType

		, FString eventTypeVersion

		, FString /* JSON STRING */ event
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_eventType;

	FString Field_eventTypeVersion;

	FString /* JSON STRING */ Field_event;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(Fevent_Event_eventBatchInsertPUT_Delegate, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uevent_Event_eventBatchInsertPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fevent_Event_eventBatchInsertPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fevent_Event_eventBatchInsertPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Batch inserts multiple events with the same event type and version", ToolTip=""), Category="HiveMP|Events")
	static Uevent_Event_eventBatchInsertPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString eventType

		, FString eventTypeVersion

		, FString /* JSON STRING */ events
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_eventType;

	FString Field_eventTypeVersion;

	FString /* JSON STRING */ Field_events;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fevent_EventTypes_typesGET_Delegate, const TArray<FHiveevent_EventTypeVersion>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uevent_EventTypes_typesGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typesGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typesGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets a list of defined event types and their current status", ToolTip="Returns a list of all of the event types and versions that are defined for this project,\nand the status of each event type version."), Category="HiveMP|Events")
	static Uevent_EventTypes_typesGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fevent_EventTypes_typeGET_Delegate, const FHiveevent_EventTypeVersion, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uevent_EventTypes_typeGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typeGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typeGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets the status of all of the versions of a specific event type", ToolTip="Returns a list of versions for the event type and their status."), Category="HiveMP|Events")
	static Uevent_EventTypes_typeGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString eventType

		, FString eventTypeVersion
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_eventType;

	FString Field_eventTypeVersion;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fevent_EventTypes_typePUT_Delegate, const FHiveevent_EventTypeVersion, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uevent_EventTypes_typePUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typePUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typePUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new event type with the specified schema", ToolTip="Creates a new event type with the specified schema."), Category="HiveMP|Events")
	static Uevent_EventTypes_typePUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString eventType

		, FString schema
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_eventType;

	FString Field_schema;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fevent_EventTypes_typePOST_Delegate, const FHiveevent_EventTypeVersion, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uevent_EventTypes_typePOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typePOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typePOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new version of an event type, with a new schema", ToolTip="Submits a new schema for the event type, creating a new version."), Category="HiveMP|Events")
	static Uevent_EventTypes_typePOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString eventType

		, FString eventTypeVersion

		, FString schema
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_eventType;

	FString Field_eventTypeVersion;

	FString Field_schema;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fevent_EventTypes_typeDELETE_Delegate, const FHiveevent_EventTypeVersion, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uevent_EventTypes_typeDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typeDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fevent_EventTypes_typeDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Schedules deletion of an event type version", ToolTip="Schedules the deletion of an event type version.  Deletion of event type versions\nare not immediate because Hive must delete all of the data stored that is associated\nwith this event type version.\n\nThis operation is irreversible, and we can not recover data deleted with this method."), Category="HiveMP|Events")
	static Uevent_EventTypes_typeDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString eventType

		, FString eventTypeVersion
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_eventType;

	FString Field_eventTypeVersion;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Game Servers GameServer"))
struct FHivegame_server_GameServer
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString templateId;

	UPROPERTY(BlueprintReadOnly)
	FString version;

	UPROPERTY(BlueprintReadOnly)
	int32 billedSliceMinutes;

	UPROPERTY(BlueprintReadOnly)
	int32 slices;

	UPROPERTY(BlueprintReadOnly)
	FString status;

	UPROPERTY(BlueprintReadOnly)
	int32 start;

	UPROPERTY(BlueprintReadOnly)
	FString serverIpAddress;

	UPROPERTY(BlueprintReadOnly)
	int32 serverPort;

	UPROPERTY(BlueprintReadOnly)
	int32 billingStart;

	UPROPERTY(BlueprintReadOnly)
	int32 billingEnd;

	UPROPERTY(BlueprintReadOnly)
	int32 expiry;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Game Servers PaginatedGameServers"))
struct FHivegame_server_PaginatedGameServers
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHivegame_server_GameServer> results;

};


struct FHivegame_server_PaginatedGameServers DeserializeFHivegame_server_PaginatedGameServers(TSharedPtr<FJsonObject> obj);



struct FHivegame_server_GameServer DeserializeFHivegame_server_GameServer(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Game Servers GameServerTemplate"))
struct FHivegame_server_GameServerTemplate
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString dockerImageName;

	UPROPERTY(BlueprintReadOnly)
	FString gcrServiceAccountJson;

	UPROPERTY(BlueprintReadOnly)
	FString containerHostPlatform;

	UPROPERTY(BlueprintReadOnly)
	int32 slices;

};


struct FHivegame_server_GameServerTemplate DeserializeFHivegame_server_GameServerTemplate(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServer_serversGET_Delegate, const FHivegame_server_PaginatedGameServers, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServer_serversGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_serversGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_serversGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieve details about game servers", ToolTip="Retrieves a paginated list of game servers from the system.  This API requires the use of\nan administration session, and is not intended to be called from within your game."), Category="HiveMP|Game Servers")
	static Ugame_server_GameServer_serversGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServer_serverGET_Delegate, const FHivegame_server_GameServer, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServer_serverGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_serverGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_serverGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieve details about an existing game server", ToolTip=""), Category="HiveMP|Game Servers")
	static Ugame_server_GameServer_serverGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServer_serverStatusPOST_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServer_serverStatusPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_serverStatusPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_serverStatusPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates the internal status of a game server instance", ToolTip=""), Category="HiveMP|Game Servers")
	static Ugame_server_GameServer_serverStatusPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString status

		, FString address

		, int32 port

		, int32 billingStart

		, int32 billingEnd
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_status;

	FString Field_address;

	int32 Field_port;

	int32 Field_billingStart;

	int32 Field_billingEnd;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServer_serverCleanupPOST_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServer_serverCleanupPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_serverCleanupPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_serverCleanupPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Cleans up a terminated server instance in Hive", ToolTip=""), Category="HiveMP|Game Servers")
	static Ugame_server_GameServer_serverCleanupPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, int32 billingStart

		, int32 billingEnd
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	int32 Field_billingStart;

	int32 Field_billingEnd;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServer_provisionPUT_Delegate, const FHivegame_server_GameServer, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServer_provisionPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_provisionPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServer_provisionPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Requests the provisioning of a game server", ToolTip="This requests the provisioning of a game server and returns the instance information.  The game\nserver is not available for connection by clients until it moves into the 'active' status."), Category="HiveMP|Game Servers")
	static Ugame_server_GameServer_provisionPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString templateId

		, FString version
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_templateId;

	FString Field_version;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServerTemplate_templateGET_Delegate, const FHivegame_server_GameServerTemplate, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServerTemplate_templateGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServerTemplate_templateGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServerTemplate_templateGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets information about an existing game server template", ToolTip=""), Category="HiveMP|Game Servers")
	static Ugame_server_GameServerTemplate_templateGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServerTemplate_templatePUT_Delegate, const FHivegame_server_GameServerTemplate, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServerTemplate_templatePUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServerTemplate_templatePUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServerTemplate_templatePUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new game server template", ToolTip=""), Category="HiveMP|Game Servers")
	static Ugame_server_GameServerTemplate_templatePUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString dockerImageName

		, FString gcrServiceAccountJson

		, FString containerHostPlatform

		, int32 slices
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_dockerImageName;

	FString Field_gcrServiceAccountJson;

	FString Field_containerHostPlatform;

	int32 Field_slices;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServerTemplate_templatePOST_Delegate, const FHivegame_server_GameServerTemplate, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServerTemplate_templatePOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServerTemplate_templatePOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServerTemplate_templatePOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates an existing game server template", ToolTip=""), Category="HiveMP|Game Servers")
	static Ugame_server_GameServerTemplate_templatePOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString dockerImageName

		, FString gcrServiceAccountJson

		, FString containerHostPlatform

		, int32 slices
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_dockerImageName;

	FString Field_gcrServiceAccountJson;

	FString Field_containerHostPlatform;

	int32 Field_slices;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fgame_server_GameServerTemplate_templateDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ugame_server_GameServerTemplate_templateDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServerTemplate_templateDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fgame_server_GameServerTemplate_templateDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Deletes a game server template", ToolTip=""), Category="HiveMP|Game Servers")
	static Ugame_server_GameServerTemplate_templateDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Integrations SteamIntegrationSummary"))
struct FHiveintegration_SteamIntegrationSummary
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString appId;

	UPROPERTY(BlueprintReadOnly)
	FString partnerPortalUsername;

	UPROPERTY(BlueprintReadOnly)
	FString connectionStatus;

	UPROPERTY(BlueprintReadOnly)
	FString lastAuthError;

	UPROPERTY(BlueprintReadOnly)
	int32 lastRecordedWishlistDate;

	UPROPERTY(BlueprintReadOnly)
	int32 lastRecordedTrafficDate;

	UPROPERTY(BlueprintReadOnly)
	int32 lastRecordedSalesDate;

};


struct FHiveintegration_SteamIntegrationSummary DeserializeFHiveintegration_SteamIntegrationSummary(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Integrations SteamGuardStatus"))
struct FHiveintegration_SteamGuardStatus
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString status;

};


struct FHiveintegration_SteamGuardStatus DeserializeFHiveintegration_SteamGuardStatus(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Integrations SteamCredentials"))
struct FHiveintegration_SteamCredentials
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString encryptedAppId;

	UPROPERTY(BlueprintReadOnly)
	FString encryptedPublisherKey;

	UPROPERTY(BlueprintReadOnly)
	FString encryptedPublisherUsername;

	UPROPERTY(BlueprintReadOnly)
	FString encryptedPublisherPassword;

	UPROPERTY(BlueprintReadOnly)
	FString encryptedPartnerSteamGuardCookie;

	UPROPERTY(BlueprintReadOnly)
	FString encryptedPartnerCurrentPoweredCookie;

	UPROPERTY(BlueprintReadOnly)
	FString encryptedPartnerCurrentGamesCookie;

	UPROPERTY(BlueprintReadOnly)
	FString encryptedPartnerCurrentGamesSessionCookie;

};


struct FHiveintegration_SteamCredentials DeserializeFHiveintegration_SteamCredentials(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Integrations SteamSaleDataState"))
struct FHiveintegration_SteamSaleDataState
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	int32 date;

	UPROPERTY(BlueprintReadOnly)
	int32 index;

};


struct FHiveintegration_SteamSaleDataState DeserializeFHiveintegration_SteamSaleDataState(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Configures Steam integration for this project", ToolTip="Calling this method sets up Steam integration for the project.  For user authentication to\nwork in steam, you need to provide at least the Steam app ID and publisher key.\n\nTo enable automated hourly analytics and sales data capture, you need to provide the username\nand plaintext password of a publisher account that can login to partner.steampowered.com.  Steam\ndoes not provide APIs for these services, so we capture data by authenticating as the specified\naccount and reading the data from the web pages.\n\nThe specified account may have Steam Guard enabled; you can check if you need to go\nthrough the Steam Guard authorization process by calling the GET method on the /steam/guard\nendpoint."), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString steamAppId

		, FString publisherKey

		, FString publisherUsername

		, FString publisherPassword
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_steamAppId;

	FString Field_publisherKey;

	FString Field_publisherUsername;

	FString Field_publisherPassword;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamStatusGET_Delegate, const FHiveintegration_SteamIntegrationSummary, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamStatusGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamStatusGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamStatusGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Get a summary of the Steam integration configuration in the project", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamStatusGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamGuardGET_Delegate, const FHiveintegration_SteamGuardStatus, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamGuardGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamGuardGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamGuardGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns the status of Steam Guard for the project", ToolTip="The Steam Guard status as reported by Hive can be one of the\nfollowing:\n\n- 'not-connected': \n  Hive has not yet attempted to connect to Steam, so we don't\n  know the status of Steam Guard on the account.\n- 'not-required':\n  Authentication was successful without providing a Steam Guard\n  cookie. This means Steam Guard is not enabled on the account.\n- 'waiting-on-steam-guard-code':\n  Hive is waiting on the Steam Guard code to be provided.  Once it has\n  been sent, call the PUT /steam/guard endpoint on the integrations API\n  in order to provide the code.\n- 'connected':\n  Hive is successfully authenticated with Steam, and the Steam Guard\n  cookie is valid."), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamGuardGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamGuardPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamGuardPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamGuardPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamGuardPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Allows you to provide a Steam Guard code if one is necessary", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamGuardPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString steamGuardCode
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_steamGuardCode;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamReimportPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamReimportPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamReimportPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamReimportPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Scheduled a full reimport of all captured Steam data", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamReimportPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamCredentialsGET_Delegate, const FHiveintegration_SteamCredentials, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamCredentialsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamCredentialsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamCredentialsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns the credentials required to authenticate with Steam", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamCredentialsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamConfiguredGET_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamConfiguredGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamConfiguredGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamConfiguredGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns if the project is configured for Steam integration", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamConfiguredGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamCredentialsGamesPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamCredentialsGamesPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamCredentialsGamesPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamCredentialsGamesPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the cookies used to connect to partner", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamCredentialsGamesPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString encryptedGamesCookie

		, FString encryptedSessionCookie
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_encryptedGamesCookie;

	FString Field_encryptedSessionCookie;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamCredentialsPoweredPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamCredentialsPoweredPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamCredentialsPoweredPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamCredentialsPoweredPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the cookie used to connect to partner", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamCredentialsPoweredPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString encryptedPoweredCookie
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_encryptedPoweredCookie;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamCredentialsGuardPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamCredentialsGuardPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamCredentialsGuardPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamCredentialsGuardPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the Steam Guard cookie", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamCredentialsGuardPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString encryptedGuardCookie

		, FString steamGuardStatus
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_encryptedGuardCookie;

	FString Field_steamGuardStatus;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamGuardStatusPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamGuardStatusPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamGuardStatusPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamGuardStatusPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the Steam Guard status", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamGuardStatusPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString steamGuardStatus
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_steamGuardStatus;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamErrormsgGET_Delegate, FString, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamErrormsgGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamErrormsgGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamErrormsgGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets the last Steam authentication error or message", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamErrormsgGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamErrormsgPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamErrormsgPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamErrormsgPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamErrormsgPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the last Steam authentication error or message", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamErrormsgPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString message
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_message;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamEmailidGET_Delegate, FString, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamEmailidGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamEmailidGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamEmailidGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets the Steam account ID associated with the last Steam Guard request", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamEmailidGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_Steam_steamEmailidPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_Steam_steamEmailidPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamEmailidPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_Steam_steamEmailidPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the Steam account ID associated with the last Steam Guard request", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_Steam_steamEmailidPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString emailId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_emailId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_SteamState_steamStateWishlistGET_Delegate, int32, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_SteamState_steamStateWishlistGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateWishlistGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateWishlistGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets the UNIX timestamp of the last recorded wishlist data", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_SteamState_steamStateWishlistGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_SteamState_steamStateWishlistPOST_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_SteamState_steamStateWishlistPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateWishlistPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateWishlistPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the UNIX timestamp of the last recorded wishlist data", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_SteamState_steamStateWishlistPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 wishlistDataDate
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_wishlistDataDate;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_SteamState_steamStateSalesGET_Delegate, const FHiveintegration_SteamSaleDataState, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_SteamState_steamStateSalesGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateSalesGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateSalesGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets the UNIX timestamp and index of the last recorded sales data", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_SteamState_steamStateSalesGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_SteamState_steamStateSalesPOST_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_SteamState_steamStateSalesPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateSalesPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateSalesPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the UNIX timestamp and index of the last recorded sales data", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_SteamState_steamStateSalesPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 salesDataDate

		, int32 salesDataIndex
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_salesDataDate;

	int32 Field_salesDataIndex;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_SteamState_steamStateTrafficGET_Delegate, int32, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_SteamState_steamStateTrafficGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateTrafficGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateTrafficGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets the UNIX timestamp of the last recorded traffic data", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_SteamState_steamStateTrafficGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fintegration_SteamState_steamStateTrafficPOST_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uintegration_SteamState_steamStateTrafficPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateTrafficPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fintegration_SteamState_steamStateTrafficPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Sets the UNIX timestamp of the last recorded traffic data", ToolTip=""), Category="HiveMP|Integrations")
	static Uintegration_SteamState_steamStateTrafficPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 trafficDataDate
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_trafficDataDate;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Game Lobbies LobbyInfo"))
struct FHivelobby_LobbyInfo
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString name;

	UPROPERTY(BlueprintReadOnly)
	FString ownerSessionId;

	UPROPERTY(BlueprintReadOnly)
	int32 currentSessions;

	UPROPERTY(BlueprintReadOnly)
	int32 maxSessions;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Game Lobbies PaginatedGameLobbies"))
struct FHivelobby_PaginatedGameLobbies
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHivelobby_LobbyInfo> results;

};


struct FHivelobby_PaginatedGameLobbies DeserializeFHivelobby_PaginatedGameLobbies(TSharedPtr<FJsonObject> obj);



struct FHivelobby_LobbyInfo DeserializeFHivelobby_LobbyInfo(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Game Lobbies ConnectedSession"))
struct FHivelobby_ConnectedSession
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString lobbyId;

	UPROPERTY(BlueprintReadOnly)
	FString sessionId;

};


struct FHivelobby_ConnectedSession DeserializeFHivelobby_ConnectedSession(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_lobbiesPaginatedGET_Delegate, const FHivelobby_PaginatedGameLobbies, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_lobbiesPaginatedGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbiesPaginatedGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbiesPaginatedGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieve a list of game lobbies", ToolTip="Retrieves a paginated list of game lobbies from the system."), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_lobbiesPaginatedGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_lobbiesGET_Delegate, const TArray<FHivelobby_LobbyInfo>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_lobbiesGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbiesGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbiesGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieve a list of the first 50 game lobbies", ToolTip="Retrieves the first 50 game lobbies."), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_lobbiesGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_lobbyGET_Delegate, const FHivelobby_LobbyInfo, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_lobbyGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbyGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbyGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves information about a game lobby", ToolTip="Retrieves information about a game lobby."), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_lobbyGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_lobbyPUT_Delegate, const FHivelobby_LobbyInfo, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_lobbyPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbyPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbyPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new game lobby", ToolTip=""), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_lobbyPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString name

		, int32 maxSessions
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_name;

	int32 Field_maxSessions;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_lobbyPOST_Delegate, const FHivelobby_LobbyInfo, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_lobbyPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbyPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbyPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates an existing game lobby, if you are the owner of it", ToolTip=""), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_lobbyPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString name

		, int32 maxSessions
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_name;

	int32 Field_maxSessions;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_lobbyDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_lobbyDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbyDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_lobbyDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Deletes a game lobby, if you are the owner of it", ToolTip="Deletes a game lobby if the current user is the owner of it.  You can not delete\ngame lobbies of other users(unless you are accessing this service using a service\nAPI key)."), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_lobbyDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_sessionsGET_Delegate, const TArray<FHivelobby_ConnectedSession>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_sessionsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_sessionsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_sessionsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Get a list of sessions that are in a game lobby", ToolTip="Get a list of sessions that are in a game lobby."), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_sessionsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_sessionGET_Delegate, const FHivelobby_ConnectedSession, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_sessionGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_sessionGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_sessionGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets information about the state of a session connected to a game lobby", ToolTip="Gets information about the state of a session connected to a game lobby."), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_sessionGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString lobbyId

		, FString sessionId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_lobbyId;

	FString Field_sessionId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_sessionPUT_Delegate, const FHivelobby_ConnectedSession, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_sessionPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_sessionPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_sessionPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Joins the specified session to a game lobby", ToolTip="Joins the specified session to the game lobby.  When using this API with a user API key, you \ncan only make this request using your own session ID.When using this API with a service API\nkey, you can join any user to a game lobby."), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_sessionPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString lobbyId

		, FString sessionId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_lobbyId;

	FString Field_sessionId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Flobby_Lobby_sessionDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ulobby_Lobby_sessionDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_sessionDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Flobby_Lobby_sessionDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Leaves or kicks a session from a game lobby", ToolTip="Leaves or kicks a session from a game lobby.  When using this API with a user API key, you \ncan only leave or kick a session from the lobby if you make this request with the authenticated session\nID, or if the authenticated session ID owns the game lobby.When using this API with a service API\nkey, you can kick any user from a game lobby."), Category="HiveMP|Game Lobbies")
	static Ulobby_Lobby_sessionDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString lobbyId

		, FString sessionId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_lobbyId;

	FString Field_sessionId;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP NAT Punchthrough NATNegotation"))
struct FHivenat_punchthrough_NATNegotation
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString host;

	UPROPERTY(BlueprintReadOnly)
	int32 port;

	UPROPERTY(BlueprintReadOnly)
	TArray<uint8> message;

};


struct FHivenat_punchthrough_NATNegotation DeserializeFHivenat_punchthrough_NATNegotation(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP NAT Punchthrough NATEndpoint"))
struct FHivenat_punchthrough_NATEndpoint
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString host;

	UPROPERTY(BlueprintReadOnly)
	int32 port;

};


struct FHivenat_punchthrough_NATEndpoint DeserializeFHivenat_punchthrough_NATEndpoint(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fnat_punchthrough_Punchthrough_punchthroughGET_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Unat_punchthrough_Punchthrough_punchthroughGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fnat_punchthrough_Punchthrough_punchthroughGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fnat_punchthrough_Punchthrough_punchthroughGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns information about an established NAT negotation, if it exists", ToolTip="Once you've made a PUT request to the service, you can check if your UDP message was received\nby the system successfully by making a call to this endpoint.If the UDP negotation was\nsuccessful, this endpoint will return true, otherwise false."), Category="HiveMP|NAT Punchthrough")
	static Unat_punchthrough_Punchthrough_punchthroughGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString session
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_session;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fnat_punchthrough_Punchthrough_punchthroughPUT_Delegate, const FHivenat_punchthrough_NATNegotation, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Unat_punchthrough_Punchthrough_punchthroughPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fnat_punchthrough_Punchthrough_punchthroughPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fnat_punchthrough_Punchthrough_punchthroughPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a NAT negotation, which you can use to send a message over UDP to punchthrough NAT", ToolTip="In order to perform NAT punchthrough, you need to send UDP messages to a dedicated server,\nwhich can't be provided directly through a REST service.  Instead, this REST service provides\nyou a server address to connect to, and the contents of a UDP message to send to that server.\nWith this information, you then need to use your language's UDP client to send the message\nto the server, which not only ensures any intermediate NATs have opened ports, but also\nfunctions to record the external port on the NAT that is available for connection from other\nusers."), Category="HiveMP|NAT Punchthrough")
	static Unat_punchthrough_Punchthrough_punchthroughPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString session
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_session;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fnat_punchthrough_Punchthrough_endpointsGET_Delegate, const TArray<FHivenat_punchthrough_NATEndpoint>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Unat_punchthrough_Punchthrough_endpointsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fnat_punchthrough_Punchthrough_endpointsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fnat_punchthrough_Punchthrough_endpointsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a list of known endpoints for a session", ToolTip="This API call returns the known endpoints for a given session ID, which you can use to\nfind the endpoints of other game sessions(for example, other players in a game lobby)\nonce they have performed NAT punchthrough."), Category="HiveMP|NAT Punchthrough")
	static Unat_punchthrough_Punchthrough_endpointsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString session
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_session;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fnat_punchthrough_Punchthrough_pingPUT_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Unat_punchthrough_Punchthrough_pingPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fnat_punchthrough_Punchthrough_pingPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fnat_punchthrough_Punchthrough_pingPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Accepts information about a NAT punchthrough UDP request from a listener", ToolTip="This method is used internally by Hive to accept information about UDP packets and store\nthe resulting NAT punchthrough information against sessions."), Category="HiveMP|NAT Punchthrough")
	static Unat_punchthrough_Punchthrough_pingPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString sessionId

		, FString hashedSecretKey

		, FString address

		, int32 port
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_sessionId;

	FString Field_hashedSecretKey;

	FString Field_address;

	int32 Field_port;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Reporting DataGroup"))
struct FHivereporting_DataGroup
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString groupName;

	UPROPERTY(BlueprintReadOnly)
	FString preferredColor;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Reporting TimeSeriesData"))
struct FHivereporting_TimeSeriesData
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	int32 timeBegin;

	UPROPERTY(BlueprintReadOnly)
	int32 timeEnd;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHivereporting_DataGroup> dataGroups;

	UPROPERTY(BlueprintReadOnly)
	FString /* JSON STRING */ dataPoints;

};


struct FHivereporting_TimeSeriesData DeserializeFHivereporting_TimeSeriesData(TSharedPtr<FJsonObject> obj);



struct FHivereporting_DataGroup DeserializeFHivereporting_DataGroup(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Reporting TimeSeriesDataPoint"))
struct FHivereporting_TimeSeriesDataPoint
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	int32 integerValue;

	UPROPERTY(BlueprintReadOnly)
	float percentValue;

	UPROPERTY(BlueprintReadOnly)
	float currencyUsdValue;

};


struct FHivereporting_TimeSeriesDataPoint DeserializeFHivereporting_TimeSeriesDataPoint(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Reporting ReportMetadata"))
struct FHivereporting_ReportMetadata
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	bool available;

	UPROPERTY(BlueprintReadOnly)
	FString title;

	UPROPERTY(BlueprintReadOnly)
	FString shortDescription;

	UPROPERTY(BlueprintReadOnly)
	FString category;

	UPROPERTY(BlueprintReadOnly)
	FString type;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Reporting PaginatedReportMetadatas"))
struct FHivereporting_PaginatedReportMetadatas
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHivereporting_ReportMetadata> results;

};


struct FHivereporting_PaginatedReportMetadatas DeserializeFHivereporting_PaginatedReportMetadatas(TSharedPtr<FJsonObject> obj);



struct FHivereporting_ReportMetadata DeserializeFHivereporting_ReportMetadata(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Reporting ReportData"))
struct FHivereporting_ReportData
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FHivereporting_ReportMetadata metadata;

	UPROPERTY(BlueprintReadOnly)
	FHivereporting_TimeSeriesData timeSeriesData;

};


struct FHivereporting_ReportData DeserializeFHivereporting_ReportData(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinVisitsWishlistsGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinVisitsWishlistsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsWishlistsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsWishlistsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which shows the number of page visits against wishlist add actions in Steam", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinVisitsWishlistsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinVisitsActionsGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinVisitsActionsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsActionsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsActionsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which shows the number of page visits against wishlist add actions and sales in Steam", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinVisitsActionsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinVisitsActionsConversionGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinVisitsActionsConversionGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsActionsConversionGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsActionsConversionGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which shows the conversion rate between page visits and wishlists / sales in Steam", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinVisitsActionsConversionGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinWishlistActionsGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinWishlistActionsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinWishlistActionsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinWishlistActionsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which breaks down wishlist actions (add, delete, purchases/activations, gifts) in Steam", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinWishlistActionsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinVisitsBreakdownDetailedGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsBreakdownDetailedGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsBreakdownDetailedGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which provides a detailed breakdown of visit sources to the store page in Steam", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinVisitsBreakdownDetailedGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinVisitsBreakdownPageGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsBreakdownPageGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinVisitsBreakdownPageGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which provides a page-grouped breakdown of visit sources to the store page in Steam", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinVisitsBreakdownPageGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which provides a unit sales breakdown by activation source", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinSalesUnitBreakdownSourceGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which provides a unit sales breakdown for Steam Store only", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinSalesUnitBreakdownSteamGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which provides a unit sales breakdown for retail (non-Steam) only", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinSalesUnitBreakdownRetailGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which provides a USD sales breakdown by activation source", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinSalesUsdBreakdownSourceGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET_Delegate, const FHivereporting_TimeSeriesData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a report which provides a USD sales breakdown for Steam Store only", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_BuiltinReports_builtinSalesUsdBreakdownSteamGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, int32 start

		, int32 end

		, int32 intervalAmount

		, FString intervalUnits
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	int32 Field_start;

	int32 Field_end;

	int32 Field_intervalAmount;

	FString Field_intervalUnits;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_Report_reportsGET_Delegate, const FHivereporting_PaginatedReportMetadatas, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_Report_reportsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_Report_reportsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_Report_reportsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Return a paginated list of reports", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_Report_reportsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Freporting_Report_reportGET_Delegate, const FHivereporting_ReportData, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Ureporting_Report_reportGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Freporting_Report_reportGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Freporting_Report_reportGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Return a paginated list of reports", ToolTip=""), Category="HiveMP|Reporting")
	static Ureporting_Report_reportGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, int32 start

		, int32 end

		, FString /* JSON STRING */ parameters
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	int32 Field_start;

	int32 Field_end;

	FString /* JSON STRING */ Field_parameters;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share InvoiceLineItem"))
struct FHiverevenue_share_InvoiceLineItem
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString invoiceId;

	UPROPERTY(BlueprintReadOnly)
	FString invoiceLineItemId;

	UPROPERTY(BlueprintReadOnly)
	FString productId;

	UPROPERTY(BlueprintReadOnly)
	FString productName;

	UPROPERTY(BlueprintReadOnly)
	FString revenueRulesetIdOverride;

	UPROPERTY(BlueprintReadOnly)
	int32 amount;

	UPROPERTY(BlueprintReadOnly)
	int32 amountFractionalDivisor;

	UPROPERTY(BlueprintReadOnly)
	FString currency;

	UPROPERTY(BlueprintReadOnly)
	int32 amountPaid;

	UPROPERTY(BlueprintReadOnly)
	int32 amountPaidFractionalDivisor;

	UPROPERTY(BlueprintReadOnly)
	bool hasRevenueShareRulesetCopy;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share Invoice"))
struct FHiverevenue_share_Invoice
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString invoiceId;

	UPROPERTY(BlueprintReadOnly)
	int32 dateCreatedUtc;

	UPROPERTY(BlueprintReadOnly)
	FString invoiceNumber;

	UPROPERTY(BlueprintReadOnly)
	FString notes;

	UPROPERTY(BlueprintReadOnly)
	FString invoicePostId;

	UPROPERTY(BlueprintReadOnly)
	int32 invoicePostedUtc;

	UPROPERTY(BlueprintReadOnly)
	FString invoicePostNotes;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_InvoiceLineItem> lineItems;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share PaginatedInvoices"))
struct FHiverevenue_share_PaginatedInvoices
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_Invoice> results;

};


struct FHiverevenue_share_PaginatedInvoices DeserializeFHiverevenue_share_PaginatedInvoices(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_Invoice DeserializeFHiverevenue_share_Invoice(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_InvoiceLineItem DeserializeFHiverevenue_share_InvoiceLineItem(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share InvoicePaymentLineItem"))
struct FHiverevenue_share_InvoicePaymentLineItem
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString paymentId;

	UPROPERTY(BlueprintReadOnly)
	FString invoiceLineItemId;

	UPROPERTY(BlueprintReadOnly)
	int32 amount;

	UPROPERTY(BlueprintReadOnly)
	int32 amountFractionalDivisor;

	UPROPERTY(BlueprintReadOnly)
	int32 sourceAmount;

	UPROPERTY(BlueprintReadOnly)
	int32 sourceAmountFractionalDivisor;

	UPROPERTY(BlueprintReadOnly)
	FString sourceCurrency;

	UPROPERTY(BlueprintReadOnly)
	float exchangeRate;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share InvoicePayment"))
struct FHiverevenue_share_InvoicePayment
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString paymentId;

	UPROPERTY(BlueprintReadOnly)
	FString invoiceId;

	UPROPERTY(BlueprintReadOnly)
	int32 dateCreatedUtc;

	UPROPERTY(BlueprintReadOnly)
	FString paymentNumber;

	UPROPERTY(BlueprintReadOnly)
	FString notes;

	UPROPERTY(BlueprintReadOnly)
	FString invoicePostId;

	UPROPERTY(BlueprintReadOnly)
	FString paymentPostId;

	UPROPERTY(BlueprintReadOnly)
	int32 paymentPostedUtc;

	UPROPERTY(BlueprintReadOnly)
	FString paymentPostNotes;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_InvoicePaymentLineItem> lineItems;

	UPROPERTY(BlueprintReadOnly)
	bool archived;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share PaginatedInvoicePayments"))
struct FHiverevenue_share_PaginatedInvoicePayments
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_InvoicePayment> results;

};


struct FHiverevenue_share_PaginatedInvoicePayments DeserializeFHiverevenue_share_PaginatedInvoicePayments(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_InvoicePayment DeserializeFHiverevenue_share_InvoicePayment(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_InvoicePaymentLineItem DeserializeFHiverevenue_share_InvoicePaymentLineItem(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share RecipientTransaction"))
struct FHiverevenue_share_RecipientTransaction
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString transactionId;

	UPROPERTY(BlueprintReadOnly)
	FString postId;

	UPROPERTY(BlueprintReadOnly)
	FString recipientId;

	UPROPERTY(BlueprintReadOnly)
	FString recipientName;

	UPROPERTY(BlueprintReadOnly)
	FString invoiceId;

	UPROPERTY(BlueprintReadOnly)
	FString paymentId;

	UPROPERTY(BlueprintReadOnly)
	int32 amount;

	UPROPERTY(BlueprintReadOnly)
	int32 amountFractionalDivisor;

	UPROPERTY(BlueprintReadOnly)
	FString currency;

};


struct FHiverevenue_share_RecipientTransaction DeserializeFHiverevenue_share_RecipientTransaction(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share Product"))
struct FHiverevenue_share_Product
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString name;

	UPROPERTY(BlueprintReadOnly)
	FString description;

	UPROPERTY(BlueprintReadOnly)
	bool visible;

	UPROPERTY(BlueprintReadOnly)
	FString /* JSON STRING */ tags;

	UPROPERTY(BlueprintReadOnly)
	FString defaultRevenueShareRulesetId;

	UPROPERTY(BlueprintReadOnly)
	FString dataCaptureProjectId;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share PaginatedProducts"))
struct FHiverevenue_share_PaginatedProducts
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_Product> results;

};


struct FHiverevenue_share_PaginatedProducts DeserializeFHiverevenue_share_PaginatedProducts(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_Product DeserializeFHiverevenue_share_Product(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share ProductSearchResult"))
struct FHiverevenue_share_ProductSearchResult
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString name;

};


struct FHiverevenue_share_ProductSearchResult DeserializeFHiverevenue_share_ProductSearchResult(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share Recipient"))
struct FHiverevenue_share_Recipient
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString name;

	UPROPERTY(BlueprintReadOnly)
	FString description;

	UPROPERTY(BlueprintReadOnly)
	int32 postDistributionTaxPercentage;

	UPROPERTY(BlueprintReadOnly)
	int32 startingBalance;

	UPROPERTY(BlueprintReadOnly)
	bool trackBalanceAndPayments;

	UPROPERTY(BlueprintReadOnly)
	bool visible;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share PaginatedRecipients"))
struct FHiverevenue_share_PaginatedRecipients
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_Recipient> results;

};


struct FHiverevenue_share_PaginatedRecipients DeserializeFHiverevenue_share_PaginatedRecipients(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_Recipient DeserializeFHiverevenue_share_Recipient(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share RecipientSearchResult"))
struct FHiverevenue_share_RecipientSearchResult
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString name;

};


struct FHiverevenue_share_RecipientSearchResult DeserializeFHiverevenue_share_RecipientSearchResult(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share RevenueShareRulesetDistribution"))
struct FHiverevenue_share_RevenueShareRulesetDistribution
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString recipientId;

	UPROPERTY(BlueprintReadOnly)
	float percentageAmount;

	UPROPERTY(BlueprintReadOnly)
	int32 fixedAmount;

	UPROPERTY(BlueprintReadOnly)
	int32 paymentLimit;

	UPROPERTY(BlueprintReadOnly)
	bool distributeFromSourceAmount;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share RevenueShareRulesetRule"))
struct FHiverevenue_share_RevenueShareRulesetRule
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_RevenueShareRulesetDistribution> distributions;

	UPROPERTY(BlueprintReadOnly)
	FString /* JSON STRING */ sourceFilters;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share RevenueShareRuleset"))
struct FHiverevenue_share_RevenueShareRuleset
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString name;

	UPROPERTY(BlueprintReadOnly)
	FString description;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_RevenueShareRulesetRule> ruleset;

	UPROPERTY(BlueprintReadOnly)
	bool visible;

};

USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share PaginatedRevenueShareRulesets"))
struct FHiverevenue_share_PaginatedRevenueShareRulesets
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHiverevenue_share_RevenueShareRuleset> results;

};


struct FHiverevenue_share_PaginatedRevenueShareRulesets DeserializeFHiverevenue_share_PaginatedRevenueShareRulesets(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_RevenueShareRuleset DeserializeFHiverevenue_share_RevenueShareRuleset(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_RevenueShareRulesetRule DeserializeFHiverevenue_share_RevenueShareRulesetRule(TSharedPtr<FJsonObject> obj);



struct FHiverevenue_share_RevenueShareRulesetDistribution DeserializeFHiverevenue_share_RevenueShareRulesetDistribution(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share RevenueShareRulesetSearchResult"))
struct FHiverevenue_share_RevenueShareRulesetSearchResult
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString name;

};


struct FHiverevenue_share_RevenueShareRulesetSearchResult DeserializeFHiverevenue_share_RevenueShareRulesetSearchResult(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Revenue Share SimulatedPayment"))
struct FHiverevenue_share_SimulatedPayment
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString recipientId;

	UPROPERTY(BlueprintReadOnly)
	FString recipientName;

	UPROPERTY(BlueprintReadOnly)
	float amount;

	UPROPERTY(BlueprintReadOnly)
	FString currency;

};


struct FHiverevenue_share_SimulatedPayment DeserializeFHiverevenue_share_SimulatedPayment(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicesGET_Delegate, const FHiverevenue_share_PaginatedInvoices, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicesGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicesGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicesGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of revenue share invoices in the system", ToolTip="Retrieves a paginated list of revenue share invoices from the system."), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicesGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoiceGET_Delegate, const FHiverevenue_share_Invoice, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoiceGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets an existing invoice in the system", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoiceGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePUT_Delegate, const FHiverevenue_share_Invoice, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new invoice", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceNumber

		, FString notes
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceNumber;

	FString Field_notes;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePOST_Delegate, const FHiverevenue_share_Invoice, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates an invoice", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId

		, FString invoiceNumber

		, FString notes
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

	FString Field_invoiceNumber;

	FString Field_notes;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePostPUT_Delegate, const FHiverevenue_share_Invoice, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePostPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePostPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePostPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Posts an invoice to the permanent record", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePostPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId

		, FString postNotes
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

	FString Field_postNotes;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoiceUnpostPUT_Delegate, const FHiverevenue_share_Invoice, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoiceUnpostPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceUnpostPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceUnpostPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Unposts an invoice from the permanent record", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoiceUnpostPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoiceItemPUT_Delegate, const FHiverevenue_share_InvoiceLineItem, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoiceItemPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceItemPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceItemPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a line item on an invoice", ToolTip="Creates a new line item on an invoice. This operation will only succeed if the invoice is not currently posted.\nWhen specifying amounts, you must provide whole numbers.  For example, if you want to specify an amount of $10.44,\nyou would pass 1044 as the amount and 100 as the fractional divisor.  The fractional divisor must go into 1,000,000\nwithout remainders."), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoiceItemPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId

		, FString productId

		, FString revenueRulesetIdOverride

		, int32 amount

		, int32 amountFractionalDivisor

		, FString currency
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

	FString Field_productId;

	FString Field_revenueRulesetIdOverride;

	int32 Field_amount;

	int32 Field_amountFractionalDivisor;

	FString Field_currency;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoiceItemPOST_Delegate, const FHiverevenue_share_InvoiceLineItem, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoiceItemPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceItemPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceItemPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates an existing line item on an invoice", ToolTip="Updates an existing line item on an invoice. This operation will only succeed if the invoice is not currently posted.\nWhen specifying amounts, you must provide whole numbers.  For example, if you want to specify an amount of $10.44,\nyou would pass 1044 as the amount and 100 as the fractional divisor.  The fractional divisor must go into 1,000,000\nwithout remainders."), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoiceItemPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId

		, FString invoiceLineItemId

		, FString productId

		, FString revenueRulesetIdOverride

		, int32 amount

		, int32 amountFractionalDivisor

		, FString currency
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

	FString Field_invoiceLineItemId;

	FString Field_productId;

	FString Field_revenueRulesetIdOverride;

	int32 Field_amount;

	int32 Field_amountFractionalDivisor;

	FString Field_currency;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoiceItemDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoiceItemDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceItemDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoiceItemDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Deletes a line item from an invoice", ToolTip="Deletes an existing line item from an invoice. This operation will only succeed if the invoice is not currently posted."), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoiceItemDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId

		, FString invoiceLineItemId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

	FString Field_invoiceLineItemId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePaymentsGET_Delegate, const FHiverevenue_share_PaginatedInvoicePayments, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePaymentsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of payments against a specified revenue share invoice", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePaymentsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId

		, FString start

		, int32 limit
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

	FString Field_start;

	int32 Field_limit;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePaymentGET_Delegate, const FHiverevenue_share_InvoicePayment, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePaymentGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets an existing payment", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePaymentGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString paymentId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_paymentId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePaymentPUT_Delegate, const FHiverevenue_share_InvoicePayment, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePaymentPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new draft payment for the invoice", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePaymentPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString invoiceId

		, FString paymentNumber

		, FString notes

		, TArray<FHiverevenue_share_InvoicePaymentLineItem> lineItems
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_invoiceId;

	FString Field_paymentNumber;

	FString Field_notes;

	TArray<FHiverevenue_share_InvoicePaymentLineItem> Field_lineItems;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePaymentPOST_Delegate, const FHiverevenue_share_InvoicePayment, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePaymentPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates an existing draft payment for the invoice", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePaymentPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString paymentId

		, FString paymentNumber

		, FString notes

		, TArray<FHiverevenue_share_InvoicePaymentLineItem> lineItems
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_paymentId;

	FString Field_paymentNumber;

	FString Field_notes;

	TArray<FHiverevenue_share_InvoicePaymentLineItem> Field_lineItems;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePaymentPostPUT_Delegate, const FHiverevenue_share_InvoicePayment, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePaymentPostPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentPostPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentPostPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Posts a payment to the system, calculating the appropriate revenue share amounts", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePaymentPostPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString paymentId

		, FString postNotes
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_paymentId;

	FString Field_postNotes;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePaymentUnpostPUT_Delegate, const FHiverevenue_share_InvoicePayment, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePaymentUnpostPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentUnpostPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentUnpostPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Unposts a payment from the system, rolling back any recipient transactions", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePaymentUnpostPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString paymentId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_paymentId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Invoice_invoicePaymentTransactionsGET_Delegate, const TArray<FHiverevenue_share_RecipientTransaction>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Invoice_invoicePaymentTransactionsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentTransactionsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Invoice_invoicePaymentTransactionsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Returns a list of transactions associated with a posted payment", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Invoice_invoicePaymentTransactionsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString paymentId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_paymentId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Product_productsGET_Delegate, const FHiverevenue_share_PaginatedProducts, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Product_productsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of products in the system", ToolTip="Retrieves a paginated list of products from the system."), Category="HiveMP|Revenue Share")
	static Urevenue_share_Product_productsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit

		, bool showHidden
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

	bool Field_showHidden;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Product_productsSearchGET_Delegate, const TArray<FHiverevenue_share_ProductSearchResult>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Product_productsSearchGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productsSearchGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productsSearchGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Searches for products based on text entry", ToolTip="Retrieves a list of product search results."), Category="HiveMP|Revenue Share")
	static Urevenue_share_Product_productsSearchGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString text
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_text;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Product_productGET_Delegate, const FHiverevenue_share_Product, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Product_productGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets an existing product in the system", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Product_productGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Product_productPUT_Delegate, const FHiverevenue_share_Product, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Product_productPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new product", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Product_productPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString name

		, FString description

		, bool visible

		, FString /* JSON STRING */ tags

		, FString defaultRevenueShareRulesetId

		, FString dataCaptureProjectId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_name;

	FString Field_description;

	bool Field_visible;

	FString /* JSON STRING */ Field_tags;

	FString Field_defaultRevenueShareRulesetId;

	FString Field_dataCaptureProjectId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Product_productPOST_Delegate, const FHiverevenue_share_Product, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Product_productPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Product_productPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates an existing product", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Product_productPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString name

		, FString description

		, bool visible

		, FString /* JSON STRING */ tags

		, FString defaultRevenueShareRulesetId

		, FString dataCaptureProjectId
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_name;

	FString Field_description;

	bool Field_visible;

	FString /* JSON STRING */ Field_tags;

	FString Field_defaultRevenueShareRulesetId;

	FString Field_dataCaptureProjectId;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Recipient_recipientsGET_Delegate, const FHiverevenue_share_PaginatedRecipients, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Recipient_recipientsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of recipients in the system", ToolTip="Retrieves a paginated list of recipients from the system."), Category="HiveMP|Revenue Share")
	static Urevenue_share_Recipient_recipientsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit

		, bool showHidden
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

	bool Field_showHidden;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Recipient_recipientsSearchGET_Delegate, const TArray<FHiverevenue_share_RecipientSearchResult>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Recipient_recipientsSearchGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientsSearchGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientsSearchGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Searches for recipients based on text entry", ToolTip="Retrieves a list of recipient search results."), Category="HiveMP|Revenue Share")
	static Urevenue_share_Recipient_recipientsSearchGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString text
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_text;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Recipient_recipientGET_Delegate, const FHiverevenue_share_Recipient, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Recipient_recipientGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets an existing recipient in the system", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Recipient_recipientGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Recipient_recipientPUT_Delegate, const FHiverevenue_share_Recipient, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Recipient_recipientPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new recipient", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Recipient_recipientPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString name

		, FString description

		, int32 postDistributionTaxPercentage

		, int32 startingBalance

		, bool trackBalanceAndPayments

		, bool visible
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_name;

	FString Field_description;

	int32 Field_postDistributionTaxPercentage;

	int32 Field_startingBalance;

	bool Field_trackBalanceAndPayments;

	bool Field_visible;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_Recipient_recipientPOST_Delegate, const FHiverevenue_share_Recipient, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_Recipient_recipientPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_Recipient_recipientPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates an existing recipient", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_Recipient_recipientPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString name

		, FString description

		, int32 postDistributionTaxPercentage

		, int32 startingBalance

		, bool trackBalanceAndPayments

		, bool visible
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_name;

	FString Field_description;

	int32 Field_postDistributionTaxPercentage;

	int32 Field_startingBalance;

	bool Field_trackBalanceAndPayments;

	bool Field_visible;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_RevenueShareRuleset_rulesetsGET_Delegate, const FHiverevenue_share_PaginatedRevenueShareRulesets, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_RevenueShareRuleset_rulesetsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of revenue share rulesets in the system", ToolTip="Retrieves a paginated list of revenue share rulesets from the system."), Category="HiveMP|Revenue Share")
	static Urevenue_share_RevenueShareRuleset_rulesetsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit

		, bool showHidden
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

	bool Field_showHidden;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_RevenueShareRuleset_rulesetsSearchGET_Delegate, const TArray<FHiverevenue_share_RevenueShareRulesetSearchResult>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_RevenueShareRuleset_rulesetsSearchGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetsSearchGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetsSearchGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Searches for rulesets based on text entry", ToolTip="Retrieves a list of ruleset search results."), Category="HiveMP|Revenue Share")
	static Urevenue_share_RevenueShareRuleset_rulesetsSearchGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString text
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_text;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_RevenueShareRuleset_rulesetGET_Delegate, const FHiverevenue_share_RevenueShareRuleset, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_RevenueShareRuleset_rulesetGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Gets an existing revenue share ruleset in the system", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_RevenueShareRuleset_rulesetGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_RevenueShareRuleset_rulesetPUT_Delegate, const FHiverevenue_share_RevenueShareRuleset, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_RevenueShareRuleset_rulesetPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new revenue share ruleset", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_RevenueShareRuleset_rulesetPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString name

		, FString description

		, TArray<FHiverevenue_share_RevenueShareRulesetRule> ruleset

		, bool visible
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_name;

	FString Field_description;

	TArray<FHiverevenue_share_RevenueShareRulesetRule> Field_ruleset;

	bool Field_visible;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_RevenueShareRuleset_rulesetPOST_Delegate, const FHiverevenue_share_RevenueShareRuleset, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_RevenueShareRuleset_rulesetPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Updates an existing revenue share ruleset", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_RevenueShareRuleset_rulesetPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id

		, FString name

		, FString description

		, TArray<FHiverevenue_share_RevenueShareRulesetRule> ruleset

		, bool visible
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

	FString Field_name;

	FString Field_description;

	TArray<FHiverevenue_share_RevenueShareRulesetRule> Field_ruleset;

	bool Field_visible;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Frevenue_share_RevenueShareRuleset_rulesetSimulatePUT_Delegate, const TArray<FHiverevenue_share_SimulatedPayment>&, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetSimulatePUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Frevenue_share_RevenueShareRuleset_rulesetSimulatePUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Simulate a revenue share ruleset against a given product and an amount", ToolTip=""), Category="HiveMP|Revenue Share")
	static Urevenue_share_RevenueShareRuleset_rulesetSimulatePUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString productId

		, float amount

		, FString currency

		, float sourceAmount

		, FString sourceCurrency

		, TArray<FHiverevenue_share_RevenueShareRulesetRule> rulesetJson
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_productId;

	float Field_amount;

	FString Field_currency;

	float Field_sourceAmount;

	FString Field_sourceCurrency;

	TArray<FHiverevenue_share_RevenueShareRulesetRule> Field_rulesetJson;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Temporary Sessions TempSession"))
struct FHivetemp_session_TempSession
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	int32 expiry;

	UPROPERTY(BlueprintReadOnly)
	int32 start;

	UPROPERTY(BlueprintReadOnly)
	int32 billedMinutes;

};


struct FHivetemp_session_TempSession DeserializeFHivetemp_session_TempSession(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Temporary Sessions TempSessionWithSecrets"))
struct FHivetemp_session_TempSessionWithSecrets
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	int32 expiry;

	UPROPERTY(BlueprintReadOnly)
	int32 start;

	UPROPERTY(BlueprintReadOnly)
	int32 billedMinutes;

	UPROPERTY(BlueprintReadOnly)
	FString apiKey;

	UPROPERTY(BlueprintReadOnly)
	FString secretKey;

};


struct FHivetemp_session_TempSessionWithSecrets DeserializeFHivetemp_session_TempSessionWithSecrets(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP Temporary Sessions PaginatedTempSessions"))
struct FHivetemp_session_PaginatedTempSessions
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString next;

	UPROPERTY(BlueprintReadOnly)
	bool moreResults;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHivetemp_session_TempSession> results;

};


struct FHivetemp_session_PaginatedTempSessions DeserializeFHivetemp_session_PaginatedTempSessions(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Ftemp_session_TemporarySession_sessionGET_Delegate, const FHivetemp_session_TempSession, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Utemp_session_TemporarySession_sessionGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySession_sessionGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySession_sessionGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves details about an existing session", ToolTip="Retrieves information about an existing temporary session, based on the session identifier.  This\ncall returns the session identifier and the expiry time of the session as a UNIX timestamp in the\nUTC timezone."), Category="HiveMP|Temporary Sessions")
	static Utemp_session_TemporarySession_sessionGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Ftemp_session_TemporarySession_sessionPUT_Delegate, const FHivetemp_session_TempSessionWithSecrets, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Utemp_session_TemporarySession_sessionPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySession_sessionPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySession_sessionPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new temporary session", ToolTip="Temporary sessions are ideal when the users playing your game are anonymous or unauthenticated; that\nis, you're not logging them in based on device identifiers, built-in device authentication, online\nproviders or the Hive account system.  Temporary sessions are created through this public API call,\nand have a built-in expiry which by default lasts 1 hour.  You can extend a session beyond the\ndefault expiry by making a POST call.\n\nHive pricing is based on user session minutes.  This means that unless otherwise possible, you\nshould explicitly DELETE a temporary session when you're finished with it.  If you do not explicitly\ndelete a session, you will be charged the number of minutes between the time the session was created\nand the time the session expires.\n\nWhen you call this method, an API key is allocated for this session.  When you call other APIs, you\nshould use the API allocated for this session, instead of the public API key you used to create the\nsession.  This call a..."), Category="HiveMP|Temporary Sessions")
	static Utemp_session_TemporarySession_sessionPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Ftemp_session_TemporarySession_sessionPOST_Delegate, const FHivetemp_session_TempSession, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Utemp_session_TemporarySession_sessionPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySession_sessionPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySession_sessionPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Reset the expiry of the temporary session", ToolTip="Resets the expiry of a temporary session to the current time, plus one hour.  You should reset the\nexpiry of a session after 30 minutes to ensure that you allow a reasonable window in case the\noperation encounters an error."), Category="HiveMP|Temporary Sessions")
	static Utemp_session_TemporarySession_sessionPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Ftemp_session_TemporarySession_sessionDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Utemp_session_TemporarySession_sessionDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySession_sessionDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySession_sessionDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Explicitly delete a temporary session", ToolTip="Explicitly deletes a temporary session based on it's identifier.  Because Hive pricing is based\non user session minutes, explicitly terminating a session will reduce your costs."), Category="HiveMP|Temporary Sessions")
	static Utemp_session_TemporarySession_sessionDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Ftemp_session_TemporarySessionAdmin_sessionsGET_Delegate, const FHivetemp_session_PaginatedTempSessions, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Utemp_session_TemporarySessionAdmin_sessionsGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySessionAdmin_sessionsGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Ftemp_session_TemporarySessionAdmin_sessionsGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves a list of temporary sessions in the system", ToolTip="Retrieves a paginated list of temporary sessions from the system.  This API requires the use of\nan administration session, and is not intended to be called from within your game."), Category="HiveMP|Temporary Sessions")
	static Utemp_session_TemporarySessionAdmin_sessionsGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString start

		, int32 limit
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_start;

	int32 Field_limit;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP UGC Cache UGCCacheItem"))
struct FHiveugc_cache_UGCCacheItem
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString lookupKey;

	UPROPERTY(BlueprintReadOnly)
	FString owner;

};


struct FHiveugc_cache_UGCCacheItem DeserializeFHiveugc_cache_UGCCacheItem(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fugc_cache_UGCCache_itemPUT_Delegate, const FHiveugc_cache_UGCCacheItem, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uugc_cache_UGCCache_itemPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fugc_cache_UGCCache_itemPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fugc_cache_UGCCache_itemPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Stores a UGC cache item in Hive", ToolTip=""), Category="HiveMP|UGC Cache")
	static Uugc_cache_UGCCache_itemPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString lookupKey

		, TArray<uint8> content
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_lookupKey;

	TArray<uint8> Field_content;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(Fugc_cache_UGCCache_contentGET_Delegate, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uugc_cache_UGCCache_contentGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fugc_cache_UGCCache_contentGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fugc_cache_UGCCache_contentGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Redirects to a public URL containing the file content", ToolTip=""), Category="HiveMP|UGC Cache")
	static Uugc_cache_UGCCache_contentGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString lookupKey
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_lookupKey;

};


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP User Sessions UserSession"))
struct FHiveuser_session_UserSession
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString accountId;

	UPROPERTY(BlueprintReadOnly)
	int32 expiry;

	UPROPERTY(BlueprintReadOnly)
	int32 start;

	UPROPERTY(BlueprintReadOnly)
	int32 billedMinutes;

};


struct FHiveuser_session_UserSession DeserializeFHiveuser_session_UserSession(TSharedPtr<FJsonObject> obj);


USTRUCT(BlueprintType, meta=(DisplayName="HiveMP User Sessions UserSessionWithSecrets"))
struct FHiveuser_session_UserSessionWithSecrets
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly)
	FString id;

	UPROPERTY(BlueprintReadOnly)
	FString accountId;

	UPROPERTY(BlueprintReadOnly)
	int32 expiry;

	UPROPERTY(BlueprintReadOnly)
	int32 start;

	UPROPERTY(BlueprintReadOnly)
	int32 billedMinutes;

	UPROPERTY(BlueprintReadOnly)
	FString apiKey;

	UPROPERTY(BlueprintReadOnly)
	FString secretKey;

};


struct FHiveuser_session_UserSessionWithSecrets DeserializeFHiveuser_session_UserSessionWithSecrets(TSharedPtr<FJsonObject> obj);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fuser_session_UserSession_sessionGET_Delegate, const FHiveuser_session_UserSession, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uuser_session_UserSession_sessionGET : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fuser_session_UserSession_sessionGET_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fuser_session_UserSession_sessionGET_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Retrieves details about an existing session", ToolTip="Retrieves information about an existing user session, based on the session identifier.  This\ncall returns the session identifier and the expiry time of the session as a UNIX timestamp in the\nUTC timezone."), Category="HiveMP|User Sessions")
	static Uuser_session_UserSession_sessionGET* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fuser_session_UserSession_sessionPUT_Delegate, const FHiveuser_session_UserSessionWithSecrets, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uuser_session_UserSession_sessionPUT : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fuser_session_UserSession_sessionPUT_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fuser_session_UserSession_sessionPUT_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Creates a new user session, by authenticating against the specified account", ToolTip="User sessions are ideal when the users playing your game are identified by either a username / password\nor by a third-party integration (such as Steam).  User sessions are created through this public API\ncall and have a built-in expiry which by default lasts 1 hour.  You can extend a session beyond the\ndefault expiry by making a POST call.\n\nHive pricing is based on user session minutes.  This means that unless otherwise possible, you\nshould explicitly DELETE a user session when you're finished with it.  If you do not explicitly\ndelete a session, you will be charged the number of minutes between the time the session was created\nand the time the session expires.\n\nWhen you call this method, an API key is allocated for this session.  When you call other APIs, you\nshould use the API allocated for this session, instead of the public API key you used to create the\nsession.  This call also provides a secret key which can be used to authorize requests on behalf\nof this session.  So..."), Category="HiveMP|User Sessions")
	static Uuser_session_UserSession_sessionPUT* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString authenticationProvider

		, FString credentials
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_authenticationProvider;

	FString Field_credentials;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fuser_session_UserSession_sessionPOST_Delegate, const FHiveuser_session_UserSession, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uuser_session_UserSession_sessionPOST : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fuser_session_UserSession_sessionPOST_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fuser_session_UserSession_sessionPOST_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Reset the expiry of the user session", ToolTip="Resets the expiry of a user session to the current time, plus one hour.  You should reset the\nexpiry of a session after 30 minutes to ensure that you allow a reasonable window in case the\noperation encounters an error."), Category="HiveMP|User Sessions")
	static Uuser_session_UserSession_sessionPOST* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fuser_session_UserSession_sessionDELETE_Delegate, bool, Result, const FHiveApiError&, Error);


UCLASS(MinimalAPI)
class Uuser_session_UserSession_sessionDELETE : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	Fuser_session_UserSession_sessionDELETE_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	Fuser_session_UserSession_sessionDELETE_Delegate OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", DisplayName="Explicitly delete a user session", ToolTip="Explicitly deletes a user session based on it's identifier.  Because Hive pricing is based\non user session minutes, explicitly terminating a session will reduce your costs."), Category="HiveMP|User Sessions")
	static Uuser_session_UserSession_sessionDELETE* PerformHiveCall(
		UObject* WorldContextObject,
		FString ApiKey

		, FString id
);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// The world context object in which this call is taking place
	UObject* WorldContextObject;

	FString ApiKey;


	FString Field_id;

};


