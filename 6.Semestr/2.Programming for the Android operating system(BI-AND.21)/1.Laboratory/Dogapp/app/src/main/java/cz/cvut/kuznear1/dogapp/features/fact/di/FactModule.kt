package cz.cvut.kuznear1.dogapp.features.fact.di

import cz.cvut.kuznear1.dogapp.features.fact.data.FactRepository
import cz.cvut.kuznear1.dogapp.features.fact.data.api.FactApiDescription
import cz.cvut.kuznear1.dogapp.features.fact.data.api.FactRemoteDataSource
import cz.cvut.kuznear1.dogapp.features.fact.presentation.FactsViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.factoryOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module
import retrofit2.Retrofit

val factModule = module {
    single { get<Retrofit>().create(FactApiDescription::class.java) }
    factoryOf(::FactRemoteDataSource)

    singleOf(::FactRepository)

    viewModelOf(::FactsViewModel)
}