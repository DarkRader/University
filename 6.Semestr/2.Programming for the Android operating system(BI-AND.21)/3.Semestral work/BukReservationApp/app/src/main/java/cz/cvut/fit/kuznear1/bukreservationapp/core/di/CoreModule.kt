package cz.cvut.fit.kuznear1.bukreservationapp.core.di

import cz.cvut.fit.kuznear1.bukreservationapp.core.data.api.RetrofitProvider
import cz.cvut.fit.kuznear1.bukreservationapp.core.data.db.BukReservationDatabase
import org.koin.android.ext.koin.androidContext
import org.koin.dsl.module

val coreModule = module {
    single { BukReservationDatabase.newInstance(androidContext()) }
    single { RetrofitProvider.provide() }
}