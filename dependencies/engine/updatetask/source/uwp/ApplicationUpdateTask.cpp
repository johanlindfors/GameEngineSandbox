#include "ApplicationUpdateTask.hpp"
#include <ppltasks.h>
#include <experimental/resumable>

using namespace updatetask;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Background;
using namespace concurrency;
using namespace Windows::System::UserProfile;
using namespace Windows::Data::Xml::Dom;
using namespace Windows::UI::Notifications;

static Windows::Foundation::DateTime ToDateTime(long long unixTime)
{
	FILETIME fileTime;
	auto ll = (unixTime * 10000000) + 116444736000000000;

	fileTime.dwLowDateTime = (DWORD)ll;
	fileTime.dwHighDateTime = ll >> 32;

	ULARGE_INTEGER universalTime;
	universalTime.LowPart = fileTime.dwLowDateTime;
	universalTime.HighPart = fileTime.dwHighDateTime;

	Windows::Foundation::DateTime dueTime;
	dueTime.UniversalTime = universalTime.QuadPart;
	return dueTime;
}

static Windows::Foundation::DateTime GetDueDateTime(long long timeInSeconds)
{
	time_t t;
	t = time(NULL);

	tm tlm;

	localtime_s(&tlm, &t);

	if (timeInSeconds <= t)
	{
		timeInSeconds = t + 5; // we need to make sure we don't try to send a notification to a time already passed, 5 seconds seems safe
	}

	return ToDateTime(timeInSeconds);
}

String ^ GetToastXml(String ^ title, String ^ message) {
	auto toastXmlString = "<toast>" + "<visual version='2'>" + "<binding template='ToastText02'>" + "<text id='1'>" + title + "</text>" + "<text id='2'>" +
						  message + "</text>" + "</binding>" + "</visual>" + "</toast>";
	return toastXmlString;
}

	Windows::Foundation::IAsyncOperation<Windows::Data::Xml::Dom::XmlDocument ^> ^
	LoadXmlAsync(Platform::String ^ filename) {
		return concurrency::create_async([filename]()
										 {
		auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;
		return concurrency::create_task(folder->GetFileAsync(filename))
			.then([](concurrency::task<Windows::Storage::StorageFile^> t) {
			return Windows::Data::Xml::Dom::XmlDocument::LoadFromFileAsync(t.get());
				}); });
	}

	void NotifyWithLocalXml(String ^ filename, String ^ id, DateTime dateTime)
{
	create_task(LoadXmlAsync(filename))
		.then([=](task<XmlDocument ^> toastDomTask)
			  {
		try {
			auto toastDOM = toastDomTask.get();
			auto toast = ref new ScheduledToastNotification(toastDOM, dateTime);
			toast->Id = id;

			ToastNotificationManager::CreateToastNotifier()->AddToSchedule(toast);
		}
		catch (...) { } })
		.get();
}

void ApplicationUpdateTask::Run(IBackgroundTaskInstance ^ taskInstance)
{
	BackgroundTaskDeferral ^ deferral = taskInstance->GetDeferral();

	try
	{
		NotifyWithLocalXml("toast.xml", "GES", GetDueDateTime(5));
	}
	catch (...)
	{
	}

	deferral->Complete();
}
