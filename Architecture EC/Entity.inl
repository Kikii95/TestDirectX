template <typename T, typename... Args>
T* AddComponent(Args&&... args) {
    for (auto* component : m_components) {
        if (dynamic_cast<T*>(component)) {
            return nullptr;
        }
    }

    T* component = new T(this, std::forward<Args>(args)...);
    component->SetID(m_id);
    m_components.push_back(component);
    return component;
}

template <typename T>
T* GetComponent() {
    for (auto* component : m_components) {
        if (T* casted = dynamic_cast<T*>(component)) {
            return casted;
        }
    }
    return nullptr;
}

template <typename T>
void RemoveComponent() {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        if (T* casted = dynamic_cast<T*>(*it)) {
            if (casted->GetID() == m_id) {
                delete* it;
                m_components.erase(it);
                return;
            }
        }
    }
}


