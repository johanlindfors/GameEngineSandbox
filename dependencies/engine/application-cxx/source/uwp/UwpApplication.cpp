#include "UwpApplication.h"
#include <concurrent_queue.h>
#include "OpenGLES.h"
#include "GLPage.h"
#include "IDispatcherWrapper.h"
#include "utilities/IOC.hpp"

using namespace std;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::ApplicationModel::Activation;
using namespace Engine;
using namespace Utilities;

class DispatcherWrapper : public IDispatcherWrapper {
public:
	DispatcherWrapper(CoreDispatcher^ dispatcher) { }

	// IDispatcherWrapper
	void ScheduleOnGameThread(const function<void()>& handler) {
		mScheduledFunctions.push(handler);
	}

	void ProcessScheduledFunctions() {
		function<void()> function;
		while (mScheduledFunctions.try_pop(function)) {
			function();
		}
	}

private:
	CoreDispatcher^ mDispatcher = { nullptr };
	concurrency::concurrent_queue<std::function<void()>> mScheduledFunctions;
};

void UwpApplication::OnLaunched(LaunchActivatedEventArgs ^)
{
	auto window = Window::Current;
	auto dispatcher = window->Dispatcher;
	auto dispatcherWrapper = make_shared<DispatcherWrapper>(dispatcher);
	IOCContainer::Instance().Register<IDispatcherWrapper>(dispatcherWrapper);

	auto openGLES = make_shared<OpenGLES>();
	auto glPage = ref new GLPage(openGLES);
	window->Content = glPage;
	window->Activate();
}
