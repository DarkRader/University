package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.di

import cz.cvut.fit.kuznear1.bukreservationapp.core.data.db.BukReservationDatabase
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.api.ReservationApiDescription
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.api.ReservationRemoteDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.db.ReservationLocalDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.ReservationRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.form.FormViewModel
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.my_reservation.MyReservationViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.factoryOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module
import retrofit2.Retrofit

val reservationModule = module {
    single { get<Retrofit>().create(ReservationApiDescription::class.java) }
    factoryOf(::ReservationRemoteDataSource)

    single { get<BukReservationDatabase>().reservationDao() }
    factoryOf(::ReservationLocalDataSource)

    singleOf(::ReservationRepository)

    viewModelOf(::FormViewModel)
    viewModelOf(::MyReservationViewModel)
}