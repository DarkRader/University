plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}

android {
    namespace = "cz.cvut.kuznear1.activitiesfragments"
    compileSdk = 34

    defaultConfig {
        applicationId = "cz.cvut.kuznear1.activitiesfragments"
        minSdk = 23
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        vectorDrawables {
            useSupportLibrary = true
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }
    buildFeatures {
        compose = true
    }
    composeOptions {
        kotlinCompilerExtensionVersion = "1.5.10"
    }
    buildFeatures {
        compose; true
    }
}

dependencies {

    implementation ("androidx.core:core-ktx:1.12.0")
    implementation ("androidx.fragment:fragment-ktx:1.6.2")
    implementation ("androidx.lifecycle:lifecycle-runtime-ktx:2.7.0")
    implementation ("androidx.appcompat:appcompat:1.6.1")
    implementation ("androidx.activity:activity-compose:1.8.2")
    implementation ("com.google.android.material:material:1.11.0")

    implementation (platform("androidx.compose:compose-bom:2024.02.01"))
    implementation ("androidx.compose.foundation:foundation")
    implementation ("androidx.compose.material:material")
    implementation ("androidx.compose.ui:ui")
    implementation ("androidx.compose.ui:ui-viewbinding")
    debugImplementation ("androidx.compose.ui:ui-tooling")
    implementation ("androidx.compose.ui:ui-tooling-preview")
}