package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.di

import cz.cvut.fit.kuznear1.rickmortyappapi.core.data.db.RickAndMortyDatabase
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.CharacterRepository
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.api.CharacterApiDescription
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.api.CharacterRemoteDataSource
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.db.CharacterLocalDataSource
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.detail.DetailViewModel
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.list.CharactersViewModel
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.search.SearchViewModel
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.favorite.FavouriteViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.factoryOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module
import retrofit2.Retrofit

val characterModule = module {
    single { get<Retrofit>().create(CharacterApiDescription::class.java) }
    factoryOf(::CharacterRemoteDataSource)

    single { get<RickAndMortyDatabase>().characterDao() }
    factoryOf(::CharacterLocalDataSource)

    singleOf(::CharacterRepository)

    viewModelOf(::DetailViewModel)
    viewModelOf(::CharactersViewModel)
    viewModelOf(::FavouriteViewModel)
    viewModelOf(::SearchViewModel)
}