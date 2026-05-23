#include "GameEngine.h"

GameEngine::GameEngine() : window(sf::VideoMode(EngineConfig::getInstance().getWidth(), EngineConfig::getInstance().getHeight()),
        EngineConfig::getInstance().getTitle()) {
    window.setFramerateLimit(60);
}

void GameEngine::init() {
    goToScene("Start");
}

void GameEngine::updateBGM(const string& path) {
    if (path.empty() || path == "none") {
        globalBGM.stop();
        currentPlayingBGMPath = "";
        return;
    }
    if (path == currentPlayingBGMPath) return;

    globalBGM.stop();
    if (globalBGM.openFromFile(path)) {
        globalBGM.setLoop(true);
        globalBGM.setVolume(40.0f);
        globalBGM.play();
        currentPlayingBGMPath = path;
    }
}

void GameEngine::goToScene(const string& id) {
    auto self = shared_from_this();

     if (id == "Start") {
         currentScene = createScene<DialogueScene>(self, vector<DialogueLine>{
             {"", "Just when I thought it couldn't get harder for me.", "assets/images/black_screen.jpg", "none", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"", "No sleep. No peace. And now, rain.", "assets/images/black_screen.jpg", "none", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"", "Next thing I need to be told is : ", "assets/images/black_screen.jpg", "none", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"", "'Caution : No wet dogs allowed inside.'", "assets/images/black_screen.jpg", "none", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"", "Would the pharmacist be mad I arrived this early?", "assets/images/outside.jpg", "none", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"", "I have never seen the doors locked before ...", "assets/images/outside.jpg", "none", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"", "... not like I have seen them open before either...", "assets/images/outside.jpg", "none", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"???", "OH! Someone is already here.", "assets/images/outside.jpg", "none", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"Pharmacist", "Sorry to keep you waiting. I didn't expect people so early.", "assets/images/outside.jpg", "assets/images/4_sprite.png", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"", "I am sorry for the early arrival...", "assets/images/outside.jpg", "assets/images/3.1_sprite.png", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"Pharmacist", "No worries.", "assets/images/outside.jpg", "assets/images/3.1_sprite.png", "none", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
             {"Pharmacist", "Here. You may enter. I can't keep you in the rain.", "assets/images/outside.jpg", "assets/images/doorun_sprite.png", "assets/sounds/opening-door.mp3", "assets/sounds/hiroshi-yoshimura-rain-mix.ogg"},
         }, "Inside", texManager, fontManager, soundManager);
     }
     else if (id == "Inside") {
         currentScene = createScene<DialogueScene>(self, vector<DialogueLine>{
             {"", "", "assets/images/Pharmacy_center.jpg", "none", "assets/sounds/close-door.mp3", "assets/sounds/nectry-antent-shelter.ogg"},
             {"Pharmacist", "While I get everything ready at the counter, you may settle down.", "assets/images/Pharmacy_center.jpg", "assets/images/3_sprite.png", "none", "assets/sounds/nectry-antent-shelter.ogg"},
             {"Pharmacist", "Why don't you look around for the time being?", "assets/images/Pharmacy_center.jpg", "assets/images/7_sprite.png", "none", "assets/sounds/nectry-antent-shelter.ogg"},
             {"", "I might as well.", "assets/images/Pharmacy_center.jpg", "none", "none", "assets/sounds/nectry-antent-shelter.ogg"},
         }, "Investigate", texManager, fontManager, soundManager);
     }
    else
        if (id == "Investigate") {
        View center;
        center.bg = "assets/images/Pharmacy_center.jpg";
        center.hotspots.push_back(sf::FloatRect(80, 100, 230, 520));
        center.messages.push_back("Hair care products? Are they any different than the store ones?");
        center.hotspots.push_back(sf::FloatRect(780, 480, 125, 90));
        center.messages.push_back("Quite a nice computer.");
        center.hotspots.push_back(sf::FloatRect(550, 600, 600, 150));
        center.messages.push_back("");
        center.exitIndex = 2;

        View left;
        left.bg = "assets/images/Pharmacy_left.jpg";
        left.hotspots.push_back(sf::FloatRect(170, 240, 430, 370));
        left.messages.push_back("... surprise... medicine... in a pharmacy...");
        left.hotspots.push_back(sf::FloatRect(525, 60, 190, 90));
        left.messages.push_back("The lights seem modern. It feels cozy.");
        left.hotspots.push_back(sf::FloatRect(890, 300, 200, 400));
        left.messages.push_back("A backroom perhaps...?");

        View right;
        right.bg = "assets/images/Pharmacy_right.jpg";
        right.hotspots.push_back(sf::FloatRect(0, 500, 150, 130));
        right.messages.push_back("Odd decore choice...");
        right.hotspots.push_back(sf::FloatRect(690, 240, 280, 500));
        right.messages.push_back("The sun isn't even out yet... Was it a good idea to come this early...?");

        currentScene = createScene<InvestigationScene>(
            self,
            vector<View>{left, center, right},
            "Counter",
            texManager,
            fontManager
        );
    }
    else if (id == "Counter") {
        currentScene = createScene<DialogueScene>(self, vector<DialogueLine>{
            {"Pharmacist", "Coming here from a prescription?", "assets/images/Pharmacy_desk.jpg", "assets/images/11_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "Or, mayhaps, just your senses acting up?", "assets/images/Pharmacy_desk.jpg", "assets/images/12_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "Both.", "assets/images/Pharmacy_desk.jpg", "assets/images/9_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "I was told to come and get this medicine if I keep having insomnia. It just so happen to be today.", "assets/images/Pharmacy_desk.jpg", "assets/images/10_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "That... is a rather unusual thing to recommend...", "assets/images/Pharmacy_desk.jpg", "assets/images/10_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "It is still better than just sending you home emptyhanded.", "assets/images/Pharmacy_desk.jpg", "assets/images/5_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "I will get the medicine right up!", "assets/images/Pharmacy_desk.jpg", "assets/images/8_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"}
         }, "Decision", texManager, fontManager, soundManager);
    }
    else if (id == "Decision") {
        currentScene = createScene<ChoiceScene>(
            "assets/images/Pharmacy_desk.jpg",
            "assets/images/8_sprite.png",
            vector<Choice>{{"You can read that?", "PathA"}, {"Is it usually this quiet here?", "PathB"}},
            texManager, fontManager);
    }
    else if (id == "PathA") {
        currentScene = createScene<DialogueScene>(self, vector<DialogueLine>{
            {"Pharmacist", "It certainly took a while to learn it.", "assets/images/Pharmacy_desk.jpg", "assets/images/3_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "But yes.", "assets/images/Pharmacy_desk.jpg", "assets/images/5_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "That is what 7 years of medical school gets you.", "assets/images/Pharmacy_desk.jpg", "assets/images/2_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "Like a cipher?", "assets/images/Pharmacy_desk.jpg", "assets/images/13_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "Akin to that. It is somewhat funny seeing patience trying to read the prescription.", "assets/images/Pharmacy_desk.jpg", "assets/images/14_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "And for it to say something completely different.", "assets/images/Pharmacy_desk.jpg", "assets/images/15_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "Yeah... funny... ha...", "assets/images/Pharmacy_desk.jpg", "assets/images/10_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "... the jokes must have come with the specialization... I assume...", "assets/images/Pharmacy_desk.jpg", "none", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "", "assets/images/Pharmacy_desk.jpg", "none", "assets/sounds/sound-effects-footsteps.ogg", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "Here... is the prescription.", "assets/images/Pharmacy_desk.jpg", "assets/images/doorun_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "It isn't that light.", "assets/images/Pharmacy_desk.jpg", "assets/images/10_sprite.png", "assets/sounds/paper-rustle.mp3", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "However, there is nothing to worry about.", "assets/images/Pharmacy_desk.jpg", "assets/images/3.1_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "Thank you... miss...", "assets/images/Pharmacy_desk.jpg", "assets/images/9_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Sienna", "Sienna...", "assets/images/Pharmacy_desk.jpg", "assets/images/12_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "Miss Sienna...", "assets/images/Pharmacy_desk.jpg", "assets/images/11_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Sienna", "Please come again!", "assets/images/Pharmacy_desk.jpg", "assets/images/15_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
        }, "End", texManager, fontManager, soundManager);
    }
    else if (id == "PathB") {
        currentScene = createScene<DialogueScene>(self, vector<DialogueLine>{
            {"Pharmacist", "Hmm?", "assets/images/Pharmacy_desk.jpg", "assets/images/2_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "If it is usually quiet as it is now. I assume many don't come here.", "assets/images/Pharmacy_desk.jpg", "assets/images/16_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "Quite the contrary. This silence is unusual.", "assets/images/Pharmacy_desk.jpg", "assets/images/10_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "I don't like noises too much, but it is up to the patient.", "assets/images/Pharmacy_desk.jpg", "assets/images/10_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "They come here to get treatment, not to have a lecture.", "assets/images/Pharmacy_desk.jpg", "assets/images/13_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "I wouldn't be able to handle that.", "assets/images/Pharmacy_desk.jpg", "assets/images/11_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "It's certainly a skill.", "assets/images/Pharmacy_desk.jpg", "assets/images/12_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "Now... the medicine... I will be back shortly...", "assets/images/Pharmacy_desk.jpg", "assets/images/doorun_aprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "", "assets/images/Pharmacy_desk.jpg", "none", "assets/sounds/sound-effects-footsteps.ogg", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "Here... is the prescription.", "assets/images/Pharmacy_desk.jpg", "assets/images/doorun_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Pharmacist", "The medication is quite strong, so please respect the instructions closely.", "assets/images/Pharmacy_desk.jpg", "assets/images/3.1_sprite.png", "assets/sounds/paper-rustle.mp3", "assets/sounds/yearning-for-trees.ogg"},
            {"", "Thank you... miss...", "assets/images/Pharmacy_desk.jpg", "assets/images/9_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Sienna", "Just Sienna.", "assets/images/Pharmacy_desk.jpg", "assets/images/12_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"", "Thank you, Sienna,", "assets/images/Pharmacy_desk.jpg", "assets/images/11_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Sienna", "I should thank you for the chit-chat.", "assets/images/Pharmacy_desk.jpg", "assets/images/4_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Sienna", "It was pleasant.", "assets/images/Pharmacy_desk.jpg", "assets/images/8_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
            {"Sienna", "Please come again!", "assets/images/Pharmacy_desk.jpg", "assets/images/15_sprite.png", "none", "assets/sounds/yearning-for-trees.ogg"},
        }, "End", texManager, fontManager, soundManager);
    }
    else if (id == "End") {
        currentScene = createScene<DialogueScene>(self, vector<DialogueLine>{
            {"", "End of concept demo. Thank you for playing!", "assets/images/black_screen.jpg", "none", "none", "assets/sounds/take-a-load-off.ogg"}
        }, "", texManager, fontManager, soundManager);
    }
}

void GameEngine::run() {
    while (window.isOpen()) {
        sf::Event event;
        bool clicked = false;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                clicked = true;
            }
        }

        sf::Vector2f mPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if (currentScene) {
            currentScene->handleInput(mPos, clicked);
            currentScene->update();
            window.clear();
            currentScene->render(window);
            window.display();
            if (currentScene->isFinished()) goToScene(currentScene->getNextSceneID());
        }
    }
}

