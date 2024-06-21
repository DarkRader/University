package cz.cvut.fit.kuznear1.firebase.features.notes.di

import cz.cvut.fit.kuznear1.firebase.features.notes.data.NotesRepository
import cz.cvut.fit.kuznear1.firebase.features.notes.presentation.NotesViewModel
import org.koin.androidx.viewmodel.dsl.viewModelOf
import org.koin.core.module.dsl.singleOf
import org.koin.dsl.module

val notesModule = module {

    singleOf(::NotesRepository)

    viewModelOf(::NotesViewModel)
}
