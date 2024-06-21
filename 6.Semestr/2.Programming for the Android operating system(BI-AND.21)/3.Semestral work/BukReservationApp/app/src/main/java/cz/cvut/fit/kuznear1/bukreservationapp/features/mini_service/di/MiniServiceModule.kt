package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.di

import cz.cvut.fit.kuznear1.bukreservationapp.core.data.db.BukReservationDatabase
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.MiniServiceRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.api.MiniServiceApiDescription
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.api.MiniServiceRemoteDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.db.MiniServiceLocalDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.list.MiniServicesViewModel
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.detail.MiniServiceDetailViewModel
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.edit.MiniServiceEditViewModel
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.add.MiniServiceAddViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.factoryOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module
import retrofit2.Retrofit

val miniServiceModule = module {
    single { get<Retrofit>().create(MiniServiceApiDescription::class.java) }
    factoryOf(::MiniServiceRemoteDataSource)

    single { get<BukReservationDatabase>().miniServiceDao() }
    factoryOf(::MiniServiceLocalDataSource)

    singleOf(::MiniServiceRepository)

    viewModelOf(::MiniServicesViewModel)
    viewModelOf(::MiniServiceDetailViewModel)
    viewModelOf(::MiniServiceEditViewModel)
    viewModelOf(::MiniServiceAddViewModel)
}