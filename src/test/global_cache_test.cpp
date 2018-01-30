//
// Created by thecharlesblake on 1/11/18.
//

#include <gtest/gtest.h>

#include "test_helper.h"
#include "../main/game/game_state.h"
#include "../main/game/global_cache.h"

typedef sol_rules::build_policy pol;

TEST(GlobalCache, BuildSameSuit) {
    test_helper::run_card_cache_test(pol::SAME_SUIT, false, false);
}

TEST(GlobalCache, BuildRedBlack) {
    test_helper::run_card_cache_test(pol::RED_BLACK, false, true);
}

TEST(GlobalCache, BuildAny) {
    test_helper::run_card_cache_test(pol::ANY_SUIT, true, true);
}

TEST(GlobalCache, BuildNone) {
    test_helper::run_card_cache_test(pol::NO_BUILD, true, true);
}

TEST(GlobalCache, CommutativeTableauPiles) {
    sol_rules rules;
    rules.tableau_pile_count = 3;
    rules.build_pol = sol_rules::build_policy::SAME_SUIT;
    game_state gs(rules, std::initializer_list<pile>{{},{},{}});
    global_cache cache(gs);

    cache.insert               (game_state(rules, {{card("AC")},{card("2D")},{card("3H")}}));
    ASSERT_TRUE (cache.contains(game_state(rules, {{card("2D")},{card("3H")},{card("AC")}})));
    ASSERT_FALSE(cache.contains(game_state(rules, {{card("3H")},{card("2D")},{card("3H")}})));

    // Test with empty piles
    cache.clear();
    cache.insert               (game_state(rules, {{card("4C")},{card("5D")},{}}));
    ASSERT_TRUE (cache.contains(game_state(rules, {{},{card("4C")},{card("5D")}})));
    ASSERT_FALSE(cache.contains(game_state(rules, {{},{card("4C")},{}})));

    // Test with piles of size > 1
    cache.clear();
    cache.insert               (game_state(rules, {{card("6C"),card("7D")},{card("8C")},{card("9D")}}));
    ASSERT_TRUE (cache.contains(game_state(rules, {{card("8C")},{card("6C"),card("7D")},{card("9D")}})));
    ASSERT_FALSE(cache.contains(game_state(rules, {{card("8C")},{card("6C"),card("KD")},{card("9D")}})));
}

TEST(GlobalCache, CommutativeReserve) {
    sol_rules rules;
    rules.reserve_size = 3;
    rules.build_pol = sol_rules::build_policy::SAME_SUIT;
    game_state gs(rules, std::initializer_list<pile>{{},{},{}});
    global_cache cache(gs);

    cache.insert               (game_state(rules, {{card("AC")},{card("2D")},{card("3H")}}));
    ASSERT_TRUE (cache.contains(game_state(rules, {{card("2D")},{card("3H")},{card("AC")}})));
    ASSERT_FALSE(cache.contains(game_state(rules, {{card("3H")},{card("2D")},{card("3H")}})));

    // Test with empty piles
    cache.clear();
    cache.insert               (game_state(rules, {{card("4C")},{card("5D")},{}}));
    ASSERT_TRUE (cache.contains(game_state(rules, {{},{card("4C")},{card("5D")}})));
    ASSERT_FALSE(cache.contains(game_state(rules, {{},{card("4C")},{}})));

    // Test with piles of size > 1
    cache.clear();
    cache.insert               (game_state(rules, {{card("6C"),card("7D")},{card("8C")},{card("9D")}}));
    ASSERT_TRUE (cache.contains(game_state(rules, {{card("8C")},{card("6C"),card("7D")},{card("9D")}})));
    ASSERT_FALSE(cache.contains(game_state(rules, {{card("8C")},{card("6C"),card("KD")},{card("9D")}})));
}

TEST(GlobalCache, CommutativeCells) {
    sol_rules rules;
    rules.cells = 3;
    rules.build_pol = sol_rules::build_policy::SAME_SUIT;
    game_state gs(rules, std::initializer_list<pile>{{},{},{}});
    global_cache cache(gs);

    cache.insert               (game_state(rules, {{card("AC")},{card("2D")},{card("3H")}}));
    ASSERT_TRUE (cache.contains(game_state(rules, {{card("2D")},{card("3H")},{card("AC")}})));
    ASSERT_FALSE(cache.contains(game_state(rules, {{card("3H")},{card("2D")},{card("3H")}})));

    // Test with empty piles
    cache.clear();
    cache.insert               (game_state(rules, {{card("4C")},{card("5D")},{}}));
    ASSERT_TRUE (cache.contains(game_state(rules, {{},{card("4C")},{card("5D")}})));
    ASSERT_FALSE(cache.contains(game_state(rules, {{},{card("4C")},{}})));
}
