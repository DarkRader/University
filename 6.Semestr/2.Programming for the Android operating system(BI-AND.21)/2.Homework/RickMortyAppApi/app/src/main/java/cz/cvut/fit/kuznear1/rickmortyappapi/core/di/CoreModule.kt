package cz.cvut.fit.kuznear1.rickmortyappapi.core.di

import cz.cvut.fit.kuznear1.rickmortyappapi.core.data.api.RetrofitProvider
import cz.cvut.fit.kuznear1.rickmortyappapi.core.data.db.RickAndMortyDatabase
import org.koin.android.ext.koin.androidContext
import org.koin.dsl.module

val coreModule = module {
    single { RickAndMortyDatabase.newInstance(androidContext()) }
    single { RetrofitProvider.provide() }
}