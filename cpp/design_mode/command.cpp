// command.cpp
#include <iostream>
#include <vector>
#include <memory>

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class Light {
public:
    void on() { std::cout << "Light is ON" << std::endl; }
    void off() { std::cout << "Light is OFF" << std::endl; }
};

class LightOnCommand : public Command {
    Light& light_;
public:
    explicit LightOnCommand(Light& light) : light_(light) {}
    void execute() override { light_.on(); }
};

class LightOffCommand : public Command {
    Light& light_;
public:
    explicit LightOffCommand(Light& light) : light_(light) {}
    void execute() override { light_.off(); }
};

class RemoteControl {
    std::vector<std::unique_ptr<Command>> commands_;
public:
    void addCommand(std::unique_ptr<Command> cmd) {
        commands_.push_back(std::move(cmd));
    }

    void executeAll() {
        for (auto& cmd : commands_) {
            cmd->execute();
        }
    }
};

int main() {
    Light livingRoomLight;
    RemoteControl remote;

    remote.addCommand(std::make_unique<LightOnCommand>(livingRoomLight));
    remote.addCommand(std::make_unique<LightOffCommand>(livingRoomLight));
    
    remote.executeAll();
    return 0;
}