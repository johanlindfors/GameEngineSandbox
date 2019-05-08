#pragma once

namespace updatetask
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class ApplicationUpdateTask sealed : Windows::ApplicationModel::Background::IBackgroundTask {
    public:
        ApplicationUpdateTask();

        virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance ^ taskInstance);
    };
}
