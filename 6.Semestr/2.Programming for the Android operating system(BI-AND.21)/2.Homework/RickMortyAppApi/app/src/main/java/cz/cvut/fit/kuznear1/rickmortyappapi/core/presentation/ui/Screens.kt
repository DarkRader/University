package cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui

sealed class Screens(val route: String) {
    data object CharactersScreen: Screens("characters")
    data object SearchScreen: Screens("search")
    data object DetailScreen: Screens("detail") {
        const val ID_KEY = "id"
    }
    data object FavouriteScreen: Screens("favourite")
}