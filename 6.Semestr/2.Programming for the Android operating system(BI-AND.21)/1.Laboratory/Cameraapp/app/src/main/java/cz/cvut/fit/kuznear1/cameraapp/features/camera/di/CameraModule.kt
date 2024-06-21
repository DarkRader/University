package cz.cvut.fit.kuznear1.cameraapp.features.camera.di

import cz.cvut.fit.kuznear1.cameraapp.features.camera.presentation.CameraViewModel
import org.koin.dsl.module

val cameraModule
    get() = module {
        factory { CameraViewModel(get()) }
    }