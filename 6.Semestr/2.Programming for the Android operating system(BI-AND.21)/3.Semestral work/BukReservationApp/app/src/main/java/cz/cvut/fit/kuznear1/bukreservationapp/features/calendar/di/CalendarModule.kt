package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.di

import cz.cvut.fit.kuznear1.bukreservationapp.core.data.db.BukReservationDatabase
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.CalendarApiDescription
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.CalendarRemoteDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db.CalendarLocalDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.CalendarRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.list.CalendarsViewModel
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.detail.CalendarDetailViewModel
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.add.CalendarAddViewModel
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.edit.CalendarEditViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.factoryOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module
import retrofit2.Retrofit

val calendarModule = module {
    single { get<Retrofit>().create(CalendarApiDescription::class.java) }
    factoryOf(::CalendarRemoteDataSource)

    single { get<BukReservationDatabase>().calendarDao() }
    factoryOf(::CalendarLocalDataSource)

    singleOf(::CalendarRepository)

    viewModelOf(::CalendarsViewModel)
    viewModelOf(::CalendarDetailViewModel)
    viewModelOf(::CalendarAddViewModel)
    viewModelOf(::CalendarEditViewModel)
}