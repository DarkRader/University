package cz.cvut.kuznear1.dogapp.features.breed.di

import cz.cvut.kuznear1.dogapp.core.data.db.DogDatabase
import cz.cvut.kuznear1.dogapp.features.breed.data.BreedRepository
import cz.cvut.kuznear1.dogapp.features.breed.data.api.BreedApiDescription
import cz.cvut.kuznear1.dogapp.features.breed.data.api.BreedRemoteDataSource
import cz.cvut.kuznear1.dogapp.features.breed.data.db.BreedLocalDataSource
import cz.cvut.kuznear1.dogapp.features.breed.presentation.detail.BreedDetailViewModel
import cz.cvut.kuznear1.dogapp.features.breed.presentation.list.BreedsViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.factoryOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module
import retrofit2.Retrofit

val breedModule = module {
    single { get<Retrofit>().create(BreedApiDescription::class.java) }
    factoryOf(::BreedRemoteDataSource)

    single { get<DogDatabase>().breedDao() }
    factoryOf(::BreedLocalDataSource)

    singleOf(::BreedRepository)

    viewModelOf(::BreedsViewModel)
    viewModelOf(::BreedDetailViewModel)
}