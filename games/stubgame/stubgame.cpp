#include <iostream>
#include "textgame.h"

using namespace skif;

class StubTextGame : public TextGame
{
public:
    std::vector<SpecInitArg> gameInputArgs() const override
    {
        return std::vector<SpecInitArg>{SpecInitArg{.argName="debug", .argComment="Just parameter", .mandatory = false}};
    }
    
    std::pair<bool,std::string> init(const ConfiguredArgValue& arg_value, std::shared_ptr<SoundController> soundcontr) override
    {
        soundcontr_ = soundcontr;
        if (arg_value.size() > 0)
        {
            std::cout << "Additional game options:\n";
            for (const auto& [option, value] : arg_value)
            {
                std::cout << option << ": " << value << "\n";
            }
            std::cout << std::endl;
        }
        soundcontr_->playBackgoundLoop("orchestral.ogg");
        return std::make_pair(true, "Демо игра-заглушка. Повторяет входящий текст. Включает музыку на фон `orchestral.ogg` и при наборе команды включает `ding.ogg`. Наберите `выход` для окончания.");
    }
    
    std::pair<GameState, std::string> processUserCmd(std::string cmd) override
    {
        soundcontr_->playEffect("ding.ogg");
        if (cmd == "выход") {
            return std::make_pair(GameState::GAMEOVER, "Всего хорошего!");
        }
        else{
            return std::make_pair(GameState::CONTINUE, std::string("Входная строка: ") + cmd + ". Продолжайте.");
        }
    }
private:
    std::shared_ptr<SoundController> soundcontr_;
};

int main(int argc, char* argv[])
{
    try {
        //1. Конструируем игру
        auto game = std::make_shared<StubTextGame>();
        //2. Запускаем главный цикл по выбранному звуковому движку и платформе
        prepareAndRunGameForPlatform(game, "Моя простая текстовая игра", argc, argv);
    }
    catch (std::exception e)
    {
        std::cout << "Exception: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}