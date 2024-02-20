#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <map>
#include <thread>
#include <tuple>

using namespace std::literals::chrono_literals;

using current_state_type = std::tuple<char, char, char>;

#define MAKE_TUPLE(x, y, z) current_state_type({x, y, z})

const std::map<current_state_type, char> state_map = {
    {MAKE_TUPLE('*', '*', '*'), ' '}, {MAKE_TUPLE('*', '*', ' '), '*'},
    {MAKE_TUPLE('*', ' ', '*'), '*'}, {MAKE_TUPLE('*', ' ', ' '), ' '},
    {MAKE_TUPLE(' ', '*', '*'), '*'}, {MAKE_TUPLE(' ', '*', ' '), '*'},
    {MAKE_TUPLE(' ', ' ', '*'), '*'}, {MAKE_TUPLE(' ', ' ', ' '), ' '}};

constexpr int GAME_SIZE = 100;

// Transform * into ' ' and vice-versa
char flip_bit(const char x) { return x == '*' ? ' ' : '*'; }

/*
 * Print out each element of the std::array
 */
template <typename T, size_t N>
void display_array(const std::array<T, N> &game_state) {
  for (const auto &i : game_state) {
    std::cout << i;
  }
  std::cout << std::endl;
}

/*
 * Iterate through the current game state, fetching the new state from the map
 */
template <size_t N> void execute_iteration(std::array<char, N> &game_state) {
  game_state[0] = flip_bit(game_state[0]);
  for (size_t i = 1; i < N - 1; ++i) {
    const std::tuple<char, char, char> current_state{
        game_state[i - 1], game_state[i], game_state[i + 1]};
    game_state[i] = state_map.at(current_state);
  }
  game_state[N - 1] = flip_bit(game_state[N - 1]);
}

int main(int argc, char **argv) {
  // Parse CLI arguments
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " ITERATION_COUNT" << std::endl;
    return 1;
  }
  size_t iteration_count = std::stoul(argv[1]);

  // Initialise new game state and display
  std::array<char, GAME_SIZE> game_state;
  game_state.fill(' ');
  display_array(game_state);

  // Begin iterations
  for (size_t i = 0; i < iteration_count; ++i) {
    execute_iteration(game_state);
    display_array(game_state);
    std::this_thread::sleep_for(50ms);
  }
  return 0;
}
