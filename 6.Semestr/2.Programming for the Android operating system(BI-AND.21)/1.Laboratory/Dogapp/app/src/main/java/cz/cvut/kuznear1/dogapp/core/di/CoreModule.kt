package cz.cvut.kuznear1.dogapp.core.di

import cz.cvut.kuznear1.dogapp.core.data.api.RetrofitProvider
import cz.cvut.kuznear1.dogapp.core.data.db.DogDatabase
import org.koin.android.ext.koin.androidContext
import org.koin.dsl.module

val coreModule = module {
    single { DogDatabase.newInstance(androidContext()) }
    single { RetrofitProvider.provide() }
}