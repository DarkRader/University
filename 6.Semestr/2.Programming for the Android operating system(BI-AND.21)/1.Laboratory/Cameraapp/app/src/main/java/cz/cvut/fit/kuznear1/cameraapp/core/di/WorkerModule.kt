package cz.cvut.fit.kuznear1.cameraapp.core.di

import cz.cvut.fit.kuznear1.cameraapp.features.notification.data.NotificationWorker
import org.koin.android.ext.koin.androidContext
import org.koin.androidx.workmanager.dsl.worker
import org.koin.dsl.module

val workerModule = module {
    worker { NotificationWorker(androidContext(), get(), get()) }
}