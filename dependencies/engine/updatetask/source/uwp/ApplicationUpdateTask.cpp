#include "ApplicationUpdateTask.h"
#include <ppltasks.h>

using namespace updatetask;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Background;
using namespace concurrency;
using namespace Windows::System::UserProfile;
using namespace Windows::Data::Xml::Dom;
using namespace Windows::UI::Notifications;

static Windows::Foundation::DateTime ToDateTime(long long unixTime) {
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

static Windows::Foundation::DateTime GetDueDateTime(long long timeInSeconds) {
	time_t t;
	t = time(NULL);

	tm tlm;

	localtime_s(&tlm, &t);

	if (timeInSeconds <= t) {
		timeInSeconds = t + 5;// we need to make sure we don't try to send a notification to a time already passed, 5 seconds seems safe
	}

	return ToDateTime(timeInSeconds);
}

String ^ GetToastXml(String ^ title, String ^ message) {
    auto toastXmlString = "<toast>" + "<visual version='2'>" + "<binding template='ToastText02'>" + "<text id='1'>" + title + "</text>" + "<text id='2'>" +
        message + "</text>" + "</binding>" + "</visual>" + "</toast>";
    return toastXmlString;
}

void Notify(String ^ title, String ^ message, String ^ id, DateTime dateTime) {
    try {
        auto toastXmlString = GetToastXml(title, message);
        auto toastDOM = ref new XmlDocument();

        toastDOM->LoadXml(toastXmlString);

        auto toast = ref new ScheduledToastNotification(toastDOM, dateTime);
        toast->Id = id;

        ToastNotificationManager::CreateToastNotifier()->AddToSchedule(toast);
    }
    catch (...) {
    }
}

ApplicationUpdateTask::ApplicationUpdateTask()
{

}

void ApplicationUpdateTask::Run(IBackgroundTaskInstance ^ taskInstance) {
    BackgroundTaskDeferral^ deferral = taskInstance->GetDeferral();

    try {
        Notify("Game Engine Sandbox", "Wanna play a game?", "GES", GetDueDateTime(5));
    } catch (...) {

    }

    deferral->Complete();
}
