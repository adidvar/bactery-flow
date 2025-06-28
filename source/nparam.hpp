#ifndef NPARAM_HPP
#define NPARAM_HPP

struct MutationSetting {
  /**
   * @brief Rate the number of mutation in percent
   */
  constexpr static float Rate = 0.1;
  /**
   * @brief Delta change of value for 1 mutation
   */
  constexpr static float Delta = 0.4;
};

#endif
