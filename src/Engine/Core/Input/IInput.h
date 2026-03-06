//
// Created by Terrarizer on 01/02/2026.
//

#ifndef DNDCREATOR_IINPUT_H
#define DNDCREATOR_IINPUT_H

class IInput {
public:
    virtual ~IInput() = default;
    [[nodiscard]] virtual bool getKey(int key) const = 0;
    [[nodiscard]] virtual bool getMouseButton(int button) const = 0;
    virtual void getMousePosition(double &x, double &y) const = 0;

    virtual void update() = 0;
    [[nodiscard]] virtual float getDeltaX() const = 0;
    [[nodiscard]] virtual float getDeltaY() const = 0;
};

#endif //DNDCREATOR_IINPUT_H