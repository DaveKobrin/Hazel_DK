#include "hzpch.h"
#include "ImGuiLayer.h"
#include "Hazel/Application.h"
#include "Hazel/InputCodes.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


namespace Hazel
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
        // Setup Dear ImGui Context
        IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		
		ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        //ImGui_ImplOpenGL3_Init(glsl_version);
        ImGui_ImplOpenGL3_Init("#version 410 core");
        
        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);
		
	}

	void ImGuiLayer::OnDetach()
	{
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
	}

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        // Rendering
        ImGui::Render();
        
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        glViewport(0, 0, app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
 //       glClearColor(1,0,1,1);
 //       glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

//        glfwSwapBuffers(window);
    }

    void ImGuiLayer::OnImGuiRender()
    {
    }
#if 0
	void ImGuiLayer::OnUpdate()
	{
	
		Application& app = Application::Get();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool showdemo = true;
		ImGui::ShowDemoWindow(&showdemo);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        UpdateMods(e.GetKeyCode(), true);

        ImGuiIO& io = ImGui::GetIO();
        io.AddKeyEvent(Key2ImGuiKey(e.GetKeyCode()), true);

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        UpdateMods(e.GetKeyCode(), false);

        ImGuiIO& io = ImGui::GetIO();
        io.AddKeyEvent(Key2ImGuiKey(e.GetKeyCode()), false);

        return false;
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(e.GetMouseButton(), true);
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(e.GetMouseButton(), false);
        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMousePosEvent(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter((unsigned int)e.GetKeyCode());
        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        //ImGuiIO& io = ImGui::GetIO();

        return false;
    }

	int ImGuiLayer::Key2ImGuiKey(const int key)
	{
        switch (key)
        {
        case HZ_KEY_TAB:            return ImGuiKey_Tab;
        case HZ_KEY_LEFT:           return ImGuiKey_LeftArrow;
        case HZ_KEY_RIGHT:          return ImGuiKey_RightArrow;
        case HZ_KEY_UP:             return ImGuiKey_UpArrow;
        case HZ_KEY_DOWN:           return ImGuiKey_DownArrow;
        case HZ_KEY_PAGE_UP:        return ImGuiKey_PageUp;
        case HZ_KEY_PAGE_DOWN:      return ImGuiKey_PageDown;
        case HZ_KEY_HOME:           return ImGuiKey_Home;
        case HZ_KEY_END:            return ImGuiKey_End;
        case HZ_KEY_INSERT:         return ImGuiKey_Insert;
        case HZ_KEY_DELETE:         return ImGuiKey_Delete;
        case HZ_KEY_BACKSPACE:      return ImGuiKey_Backspace;
        case HZ_KEY_SPACE:          return ImGuiKey_Space;
        case HZ_KEY_ENTER:          return ImGuiKey_Enter;
        case HZ_KEY_ESCAPE:         return ImGuiKey_Escape;
        case HZ_KEY_APOSTROPHE:     return ImGuiKey_Apostrophe;
        case HZ_KEY_COMMA:          return ImGuiKey_Comma;
        case HZ_KEY_MINUS:          return ImGuiKey_Minus;
        case HZ_KEY_PERIOD:         return ImGuiKey_Period;
        case HZ_KEY_SLASH:          return ImGuiKey_Slash;
        case HZ_KEY_SEMICOLON:      return ImGuiKey_Semicolon;
        case HZ_KEY_EQUAL:          return ImGuiKey_Equal;
        case HZ_KEY_LEFT_BRACKET:   return ImGuiKey_LeftBracket;
        case HZ_KEY_BACKSLASH:      return ImGuiKey_Backslash;
        case HZ_KEY_RIGHT_BRACKET:  return ImGuiKey_RightBracket;
        case HZ_KEY_GRAVE_ACCENT:   return ImGuiKey_GraveAccent;
        case HZ_KEY_CAPS_LOCK:      return ImGuiKey_CapsLock;
        case HZ_KEY_SCROLL_LOCK:    return ImGuiKey_ScrollLock;
        case HZ_KEY_NUM_LOCK:       return ImGuiKey_NumLock;
        case HZ_KEY_PRINT_SCREEN:   return ImGuiKey_PrintScreen;
        case HZ_KEY_PAUSE:          return ImGuiKey_Pause;
        case HZ_KEY_KP_0:           return ImGuiKey_Keypad0;
        case HZ_KEY_KP_1:           return ImGuiKey_Keypad1;
        case HZ_KEY_KP_2:           return ImGuiKey_Keypad2;
        case HZ_KEY_KP_3:           return ImGuiKey_Keypad3;
        case HZ_KEY_KP_4:           return ImGuiKey_Keypad4;
        case HZ_KEY_KP_5:           return ImGuiKey_Keypad5;
        case HZ_KEY_KP_6:           return ImGuiKey_Keypad6;
        case HZ_KEY_KP_7:           return ImGuiKey_Keypad7;
        case HZ_KEY_KP_8:           return ImGuiKey_Keypad8;
        case HZ_KEY_KP_9:           return ImGuiKey_Keypad9;
        case HZ_KEY_KP_DECIMAL:     return ImGuiKey_KeypadDecimal;
        case HZ_KEY_KP_DIVIDE:      return ImGuiKey_KeypadDivide;
        case HZ_KEY_KP_MULTIPLY:    return ImGuiKey_KeypadMultiply;
        case HZ_KEY_KP_SUBTRACT:    return ImGuiKey_KeypadSubtract;
        case HZ_KEY_KP_ADD:         return ImGuiKey_KeypadAdd;
        case HZ_KEY_KP_ENTER:       return ImGuiKey_KeypadEnter;
        case HZ_KEY_KP_EQUAL:       return ImGuiKey_KeypadEqual;
        case HZ_KEY_LEFT_SHIFT:     return ImGuiKey_LeftShift;
        case HZ_KEY_LEFT_CONTROL:   return ImGuiKey_LeftCtrl;
        case HZ_KEY_LEFT_ALT:       return ImGuiKey_LeftAlt;
        case HZ_KEY_LEFT_SUPER:     return ImGuiKey_LeftSuper;
        case HZ_KEY_RIGHT_SHIFT:    return ImGuiKey_RightShift;
        case HZ_KEY_RIGHT_CONTROL:  return ImGuiKey_RightCtrl;
        case HZ_KEY_RIGHT_ALT:      return ImGuiKey_RightAlt;
        case HZ_KEY_RIGHT_SUPER:    return ImGuiKey_RightSuper;
        case HZ_KEY_MENU:           return ImGuiKey_Menu;
        case HZ_KEY_0:              return ImGuiKey_0;
        case HZ_KEY_1:              return ImGuiKey_1;
        case HZ_KEY_2:              return ImGuiKey_2;
        case HZ_KEY_3:              return ImGuiKey_3;
        case HZ_KEY_4:              return ImGuiKey_4;
        case HZ_KEY_5:              return ImGuiKey_5;
        case HZ_KEY_6:              return ImGuiKey_6;
        case HZ_KEY_7:              return ImGuiKey_7;
        case HZ_KEY_8:              return ImGuiKey_8;
        case HZ_KEY_9:              return ImGuiKey_9;
        case HZ_KEY_A:              return ImGuiKey_A;
        case HZ_KEY_B:              return ImGuiKey_B;
        case HZ_KEY_C:              return ImGuiKey_C;
        case HZ_KEY_D:              return ImGuiKey_D;
        case HZ_KEY_E:              return ImGuiKey_E;
        case HZ_KEY_F:              return ImGuiKey_F;
        case HZ_KEY_G:              return ImGuiKey_G;
        case HZ_KEY_H:              return ImGuiKey_H;
        case HZ_KEY_I:              return ImGuiKey_I;
        case HZ_KEY_J:              return ImGuiKey_J;
        case HZ_KEY_K:              return ImGuiKey_K;
        case HZ_KEY_L:              return ImGuiKey_L;
        case HZ_KEY_M:              return ImGuiKey_M;
        case HZ_KEY_N:              return ImGuiKey_N;
        case HZ_KEY_O:              return ImGuiKey_O;
        case HZ_KEY_P:              return ImGuiKey_P;
        case HZ_KEY_Q:              return ImGuiKey_Q;
        case HZ_KEY_R:              return ImGuiKey_R;
        case HZ_KEY_S:              return ImGuiKey_S;
        case HZ_KEY_T:              return ImGuiKey_T;
        case HZ_KEY_U:              return ImGuiKey_U;
        case HZ_KEY_V:              return ImGuiKey_V;
        case HZ_KEY_W:              return ImGuiKey_W;
        case HZ_KEY_X:              return ImGuiKey_X;
        case HZ_KEY_Y:              return ImGuiKey_Y;
        case HZ_KEY_Z:              return ImGuiKey_Z;
        case HZ_KEY_F1:             return ImGuiKey_F1;
        case HZ_KEY_F2:             return ImGuiKey_F2;
        case HZ_KEY_F3:             return ImGuiKey_F3;
        case HZ_KEY_F4:             return ImGuiKey_F4;
        case HZ_KEY_F5:             return ImGuiKey_F5;
        case HZ_KEY_F6:             return ImGuiKey_F6;
        case HZ_KEY_F7:             return ImGuiKey_F7;
        case HZ_KEY_F8:             return ImGuiKey_F8;
        case HZ_KEY_F9:             return ImGuiKey_F9;
        case HZ_KEY_F10:            return ImGuiKey_F10;
        case HZ_KEY_F11:            return ImGuiKey_F11;
        case HZ_KEY_F12:            return ImGuiKey_F12;
        default:                    return ImGuiKey_None;
        }        
	}

    void ImGuiLayer::UpdateMods(const int key, const bool isPressed)
    {
        ImGuiIO& io = ImGui::GetIO();

        switch (key)
        {
        case HZ_KEY_LEFT_CONTROL:
        case HZ_KEY_RIGHT_CONTROL:
            io.AddKeyEvent(ImGuiKey_ModCtrl, isPressed);
            break;
        case HZ_KEY_LEFT_SHIFT:
        case HZ_KEY_RIGHT_SHIFT:
            io.AddKeyEvent(ImGuiKey_ModShift, isPressed);
            break;
        case HZ_KEY_LEFT_ALT:
        case HZ_KEY_RIGHT_ALT:
            io.AddKeyEvent(ImGuiKey_ModAlt, isPressed);
            break;
        case HZ_KEY_LEFT_SUPER:
        case HZ_KEY_RIGHT_SUPER:
            io.AddKeyEvent(ImGuiKey_ModSuper, isPressed);
            break;
        }
    }
#endif

}
