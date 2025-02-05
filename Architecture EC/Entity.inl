template <typename T, typename... Args>
T* Entity::AddComponent(Args&&... args) {
    std::type_index typeID = std::type_index(typeid(T));
    if (m_components.find(typeID) == m_components.end()) {
        T* component = new T(this, std::forward<Args>(args)...);
        m_components[typeID] = component;
        return component;
    }
    return nullptr;
}

template <typename T>
T* Entity::GetComponent() {
    std::type_index typeID = std::type_index(typeid(T));
    if (m_components.find(typeID) != m_components.end()) {
        return static_cast<T*>(m_components[typeID]);
    }
    return nullptr;
}

template <typename T>
void Entity::RemoveComponent() {
    std::type_index typeID = std::type_index(typeid(T));
    auto it = m_components.find(typeID);
    if (it != m_components.end()) {
        delete it->second;
        m_components.erase(it);
    }
}

//dynamicCast (au lieu de type_index et doc rester sur vector au lieu map)
//T::ID == GetId() plutot que typeID