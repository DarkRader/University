package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.di

import cz.cvut.fit.kuznear1.bukreservationapp.core.data.db.BukReservationDatabase
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.api.ProfileApiDescription
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.api.ProfileRemoteDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.db.ProfileLocalDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.presentation.main_page.ProfileViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.factoryOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module
import retrofit2.Retrofit

val profileModule = module {
    single { get<Retrofit>().create(ProfileApiDescription::class.java) }
    factoryOf(::ProfileRemoteDataSource)

    single { get<BukReservationDatabase>().profileDao() }
    factoryOf(::ProfileLocalDataSource)

    singleOf(::ProfileRepository)

    viewModelOf(::ProfileViewModel)
}