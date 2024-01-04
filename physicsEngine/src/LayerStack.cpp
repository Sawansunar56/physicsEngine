#include "precompPch.h"
#include "LayerStack.h"

LayerStack::LayerStack() {}
LayerStack::~LayerStack() {
    for (Layer *layer : m_Layers) {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer *layer) {
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
}

void LayerStack::PushOverLay(Layer *overlay) { m_Layers.emplace_back(overlay); }

void LayerStack::PopLayer(Layer *layer) {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

void LayerStack::PopverLay(Layer *overlay) {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
    }
}
