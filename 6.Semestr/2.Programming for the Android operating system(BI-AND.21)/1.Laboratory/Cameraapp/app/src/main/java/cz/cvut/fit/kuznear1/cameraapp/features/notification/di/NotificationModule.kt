package cz.cvut.fit.kuznear1.cameraapp.features.notification.di

import cz.cvut.fit.kuznear1.cameraapp.features.notification.data.NotificationHelper
import org.koin.dsl.module

val notificationModule
    get() = module {
        single { NotificationHelper() }
    }