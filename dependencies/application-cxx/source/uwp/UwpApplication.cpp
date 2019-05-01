#include "UwpApplication.h"
#include <concurrent_queue.h>
// #include "OpenGLES.h"
// #include "GLPage.h"
#include "IDispatcherWrapper.h"
#include "IOC.hpp"

using namespace std;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::ApplicationModel::Activation;
using namespace Engine;
using namespace Utilities;

class DispatcherWrapper : public IDispatcherWrapper {
public:
	DispatcherWrapper(Windows::UI::Core::CoreDispatcher^ dispatcher) {

	}

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
	Windows::UI::Core::CoreDispatcher^ mDispatcher = { nullptr };
	concurrency::concurrent_queue<std::function<void()>> mScheduledFunctions;
};

void UwpApplication::OnLaunched(LaunchActivatedEventArgs ^)
{
	auto window = Window::Current;
	auto dispatcherWrapper = make_shared<DispatcherWrapper>(window->Dispatcher);
	IOCContainer::Instance().Register<IDispatcherWrapper>(dispatcherWrapper);
	
	//auto glPage = make<GLPage>(make_shared<OpenGLES>());
	//window.Content(glPage);
	window->Activate();
}
