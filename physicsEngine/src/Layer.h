#pragma once

#include "precompPch.h"
#include "events/Event.h"
#include "utils/Timestep.h"

class Layer {
  public:
    Layer(const std::string &name = "Layer");
    virtual ~Layer();

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate(Timestep ts) {}
    virtual void onEvent(Event &e) {}
    virtual void onImGuiRender() {}

    inline const std::string &GetName() const { return m_DebugName; }

  protected:
    std::string m_DebugName;
};
