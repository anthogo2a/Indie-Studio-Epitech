/*
** EPITECH PROJECT, 2021
** Player
** File description:
** Player
*/

#include <valarray>
#include "Player.hpp"

Player::Player(std::string texture_path, Vector3 position, std::vector<Model> *models) : Object(texture_path, models, position),
                                   Collide(GetMeshBoundingBox(_models->at(0).meshes[0]), _position)
{
    _bbox.max.x -= 0.1;
    _bbox.min.x += 0.1;
    _i_input = nullptr;
    _bombs = new std::vector<Bomb *>();
    _dead = false;
    _tmp_action_bot = NULL_ACTION;
    _bot_cool_down = 0;
    _ia = false;

    _length_ray = 2;
    _max_bombs = 1;
    _speed = 0.1;
    _wall_pass = false;
}

Player::~Player()
{
}

bool Player::do_clip_on_axis(const float *offset_axis, float *new_position)
{
    if (*offset_axis > 0.3 && *offset_axis < 1.5) {
        *new_position -= _speed;
        return (true);
    }
    if (*offset_axis > 2.5 && *offset_axis < 3.7) {
        *new_position += _speed;
        return (true);
    }
    return (false);
}

Vector3 Player::clipMovement(Action dir)
{
    Vector3 new_position = _position;

    float offset_axis_z = std::fmod(std::abs(_position.z + 14), 4.0f);
    float offset_axis_x = std::fmod(std::abs(_position.x + 20), 4.0f);

    switch (dir) {
        case RIGHT:
            _direction = 90.0f;
            if (!do_clip_on_axis(&offset_axis_z, &new_position.z))
                new_position.x += _speed;
            _animating = true;
            break;
        case LEFT:
            _direction = -90.0f;
            if (!do_clip_on_axis(&offset_axis_z, &new_position.z))
                new_position.x -= _speed;
            _animating = true;
            break;
        case UP:
            _direction = 0.0f;
            if (!do_clip_on_axis(&offset_axis_x, &new_position.x))
                new_position.z -= _speed;
            _animating = true;
            break;
        case DOWN:
            _direction = 180.0f;
            if (!do_clip_on_axis(&offset_axis_x, &new_position.x))
                new_position.z += _speed;
            _animating = true;
            break;
    }

    return (new_position);
}

void Player::update(std::vector<Collide *> walls, std::vector<Collide *> crates, std::vector<Collide *> bombs, Hud *hud)
{
    hud->update(_dead, _max_bombs, _length_ray - 1, _speed * 10, _wall_pass);
    if (_dead || _ia) return;

    Action action = _i_input->getAction();
    if (action == NULL_ACTION) {
        _pos_models = 0;
        _animating = false;
        return;
    }
    Vector3 new_position = clipMovement(action);

    if (new_position.x != _position.x || new_position.z != _position.z)
        moveTo(new_position, walls, crates, bombs);
}

bool Player::BotTryDir(Vector3 new_position, std::vector<Collide *> other)
{
    Vector3 prev_position = _position;
    _position = new_position;
    _bbox = setNewPosBBox(_bbox, prev_position, new_position);

    if (doCollide(other)) {
        _bbox = setNewPosBBox(_bbox, new_position, prev_position);
        _position = prev_position;
        return false;
    }
    _bbox = setNewPosBBox(_bbox, new_position, prev_position);
    _position = prev_position;
    return true;
}

void Player::updateBot(std::vector<Collide *> players, std::vector<Collide *> crates, std::vector<Collide *> walls, std::vector<Collide *> bombs)
{
    if (_tmp_action_bot == A_BUTTON) {
        if (_dir_bomb == DOWN) _tmp_action_bot = UP;
        if (_dir_bomb == UP) _tmp_action_bot = DOWN;
        if (_dir_bomb == LEFT) _tmp_action_bot = RIGHT;
        if (_dir_bomb == RIGHT) _tmp_action_bot = LEFT;
    }

    Vector3 new_position = _position;

    switch (_tmp_action_bot) {
        case RIGHT:
            _direction = 90.0f;
            new_position.x += _speed;
            _animating = true;
            break;
        case LEFT:
            _direction = -90.0f;
            new_position.x -= _speed;
            _animating = true;
            break;
        case UP:
            _direction = 0.0f;
            new_position.z -= _speed;
            _animating = true;
            break;
        case DOWN:
            _direction = 180.0f;
            new_position.z += _speed;
            _animating = true;
            break;
        case NULL_ACTION:
            _pos_models = 0;
            _animating = false;
            break;
    }

    std::vector<Action> possible = {UP, DOWN, LEFT, RIGHT};
    for (int i = 0; i < possible.size(); i++) {
        if (_bombs->size() != 0 && possible[i] == _dir_bomb)
            possible.erase(possible.begin() + i);
    }

    if (new_position.x != _position.x || new_position.z != _position.z) {
        if (!BotTryDir(new_position, walls))
            _tmp_action_bot = possible[std::rand() % possible.size()];
        if (!BotTryDir(new_position, crates) || !BotTryDir(new_position, bombs) || !BotTryDir(new_position, players)) {
            if (_bombs->empty()) {
                if (_bot_cool_down <= 0) {
                    _dir_bomb = _tmp_action_bot;
                    _tmp_action_bot = A_BUTTON;
                    _bot_cool_down = 100;
                }
                _bot_cool_down--;
            }
        }
        moveTo(new_position, walls, crates, bombs);
    }
}

float Player::center_clip(const float pos)
{
    int to_clip = (int)pos;
    if (to_clip == 0) return (0);

    for (int i = 1; i < 18; i += 2) {
        if (abs(to_clip) >= i && abs(to_clip) < i + 2) {
            if (to_clip > 0) return ((float)(i + 1));
            else return ((float)(-i - 1));
        }
    }
    return 0;
}

bool Player::checkBombs(std::vector<Bomb *> *bombs, std::vector<Collide *> crates, std::vector<Model> *models)
{
    if (_dead) return (false);

    bool destroyed;
    for (int o = 0; o < _bombs->size(); o++) {
        destroyed = true;
        for (int i = 0; i < bombs->size(); i++) {
            if (_bombs->at(o) == bombs->at(i)) destroyed = false;
        }
        if (destroyed) _bombs->erase(_bombs->begin() + o);
    }

    Action action;
    if (_ia) action = getActionBot();
    else action = _i_input->getAction();

    if (action != A_BUTTON) return (false);
    if (_bombs->size() >= _max_bombs) return (false);
    if (_wall_pass && doCollide(crates)) return (false);

    bombs->push_back(new Bomb({center_clip(_position.x), _position.y, center_clip(_position.z)}, models, _length_ray));
    _bombs->emplace_back(bombs->back());
}

bool Player::moveTo(Vector3 new_position, std::vector<Collide *> others, std::vector<Collide *> crates, std::vector<Collide *> bombs)
{
    Vector3 prev_position = _position;
    _position = new_position;
    _bbox = setNewPosBBox(_bbox, prev_position, new_position);

    std::vector<Bomb *> no_collide_bombs;
    for (int i = 0; i < _bombs->size(); i++) {
        if (_bombs->at(i)->_no_collide) {
            if (!doCollide(_bombs->at(i))) _bombs->at(i)->_no_collide = false;
            no_collide_bombs.push_back(_bombs->at(i));
        }
    }
    std::vector<Collide *> filtered;
    for (int i = 0; i < others.size(); i++)
        filtered.emplace_back(others[i]);

    bool not_filtered = true;
    for (int i = 0; i < bombs.size(); not_filtered = true, i++) {
        for (int o = 0; o < no_collide_bombs.size(); o++)
            if (bombs[i] == no_collide_bombs[o]) not_filtered = false;
        if (not_filtered) filtered.emplace_back(bombs[i]);
    }
    for (int i = 0; !_wall_pass && i < crates.size(); i++)
        filtered.emplace_back(crates[i]);

    if (doCollide(filtered)) {
        _bbox = setNewPosBBox(_bbox, new_position, prev_position);
        _position = prev_position;
        return false;
    }
    return true;
}


void Player::setInput(IInput *i_input)
{
    _i_input = i_input;
}

IInput *Player::getInput()
{
    return (_i_input);
}

void Player::destroy()
{
    moveTo({-18, 0, -12}, std::vector<Collide *>(), std::vector<Collide *>(), std::vector<Collide *>());
    _dead = true;
}

bool Player::isAlive()
{
    return (!_dead);
}

void Player::powerUp(PowerUpTypes type)
{
    switch (type) {
        case PowerUpTypes::BOMB_UP:
            _max_bombs += 1;
            break;
        case PowerUpTypes::SPEED_UP:
            if (_speed < 0.2) _speed += 0.025f;
            break;
        case PowerUpTypes::RANGE_UP:
            if (_length_ray != 5) _length_ray += 1;
            break;
        case PowerUpTypes::WALL_PASS:
            _wall_pass = true;
            break;
    }
}

void Player::pack()
{
    std::string save;
    save = this->_path_texture + " " + std::to_string(this->_position.x) + " " + std::to_string(this->_position.y) + " " + std::to_string(this->_position.z)
           + " " + std::to_string(_ia) + " "+ std::to_string(_dead) + " " + std::to_string(this->_length_ray)  + " " + std::to_string(this->_max_bombs)
           + " " + std::to_string(this->_speed) + " " + std::to_string(this->_wall_pass) + "\n";
    std::ofstream myfile("SAVE_DIR/Player_save", std::ios_base::app);
    if (myfile.is_open()) {
        myfile << save;
        myfile.close();
    }
    else
        std::cerr << "Unable to open file" << std::endl;
    myfile.close();
}

Player *Player::unpack(int nb, std::vector<Model> *models)
{
    std::ifstream myfile;
    std::vector<std::string> vect;
    myfile.open("SAVE_DIR/Player_save_tmp");
    std::string line;
    getline(myfile, line);
    std::istringstream ss(line);
    std::string ok;
    while (ss >> ok)
        vect.push_back(ok);
    Vector3 pos;
    pos.x = std::stof(vect.at(1).c_str());
    pos.y = std::stof(vect.at(2).c_str());
    pos.z = std::stof(vect.at(3).c_str());
    auto p1 = new  Player(vect.at(0), pos, models);
    p1->_ia = stoi(vect.at(4));
    p1->_dead = stoi(vect.at(5));
    p1->_length_ray = stoi(vect.at(6));
    p1->_max_bombs = stoi(vect.at(7));
    p1->_speed = stof(vect.at(8));
    p1->_wall_pass = stoi(vect.at(9));
    delete_line("SAVE_DIR/Player_save_tmp", 0);
    myfile.close();
    return (p1);
}

Action Player::getActionBot()
{
    return (_tmp_action_bot);
}
