package cz.cvut.fit.kuznear1.firebase.features.profile.di

import cz.cvut.fit.kuznear1.firebase.features.profile.data.UserRepository
import cz.cvut.fit.kuznear1.firebase.features.profile.presentation.ProfileViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module

val profileModule = module {

    singleOf(::UserRepository)

    viewModelOf(::ProfileViewModel)
}
