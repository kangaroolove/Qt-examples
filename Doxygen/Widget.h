/**
 * @file Widget.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-02-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <QWidget>

/**
 * @brief This is a basic class
 *
 */

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  /**
   * @brief This function is for printing a int
   *
   * @param number
   */
  void printInt(const int &number);

  /**
   * @brief This function will return a bool
   *
   * @return true If you are right
   * @return false If you are wrong
   * @see printInt(const int& number)
   * @note This is a note
   * @attention This is an attention
   * @warning This is a warning
   */
  bool isBool();
};