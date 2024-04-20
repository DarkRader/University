package cz.cvut.fit.localstorage.profile

enum class DarkMode(val id: Int, val displayName: String) {

    On(id = 0, displayName = "On"),
    Off(id = 1, displayName = "Off"),
    System(id = 2, displayName = "System"),
}
