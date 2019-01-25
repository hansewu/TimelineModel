// Undo Library
// Copyright (C) 2015-2017 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef UNDO_STATE_H_INCLUDED
#define UNDO_STATE_H_INCLUDED
#pragma once

#include "undo_command.h"

namespace undo {

  class UndoCommand;
  class UndoHistory;

  // Represents a state that can be undone. If we are in this state,
  // is because the command was already executed.
  class UndoState {
    friend class UndoHistory;
  public:
    UndoState(UndoCommand* cmd)
      : m_prev(nullptr)
      , m_next(nullptr)
      , m_parent(nullptr)
      , m_cmd(cmd) {
    }

    ~UndoState() {
      if (m_cmd)
        m_cmd->dispose();

#ifdef _DEBUG
      m_prev = nullptr;
      m_next = nullptr;
      m_parent = nullptr;
      m_cmd = nullptr;
#endif
    }

    UndoState* prev() const { return m_prev; }
    UndoState* next() const { return m_next; }
    UndoCommand* cmd() const { return m_cmd; }
  private:
    UndoState* m_prev;
    UndoState* m_next;
    UndoState* m_parent;             // Parent state, after we undo
    UndoCommand* m_cmd;
  };

} // namespace undo

#endif  // STATE_H_INCLUDED
