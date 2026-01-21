//
// Created by Terrarizer on 21/01/2026.
//

#ifndef DNDCREATOR_IWINDOW_H
#define DNDCREATOR_IWINDOW_H

class IWindow {
public:
    virtual ~IWindow() = default;

    /**
     * Initializes the window, called at the start/initialization of the engine
     * @return Returns true if successful and false if not
     */
    virtual bool initialize() = 0;

    /**
     * Creates a new window and sets it as the context
     * @return Returns true if successful and false if not
     */
    virtual bool createWindow(int width, int height, const char* window_name = "Default") = 0;

    /**
     * Checks if the window is closed or not
     * @return returns true if it should close and false if not
     */
    [[nodiscard]] virtual bool shouldClose() const = 0;

    /**
     * Calls the window library's PollEvents function (if it has it)
     */
    virtual void pollEvents() = 0;

    /**
     * Swaps the screen buffers, should be called at the end of the main loop
     */
    virtual void swapBuffers() = 0;

    /**
     * Terminates the window
     * @return Returns true if successful and false if not
     */
    virtual bool shutdown() = 0;
};

#endif //DNDCREATOR_IWINDOW_H