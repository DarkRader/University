import java.util.Properties
import java.io.FileInputStream

val keystorePropertiesFile = rootProject.file("local.properties")
val keystoreProperties = Properties()
keystoreProperties.load(FileInputStream(keystorePropertiesFile))


plugins {
    alias(libs.plugins.androidApplication)
    alias(libs.plugins.jetbrainsKotlinAndroid)
}

android {
    namespace = "cz.cvut.fit.kuznear1.releaseapp"
    compileSdk = 34

    defaultConfig {
        applicationId = "cz.cvut.fit.kuznear1.releaseapp"
        minSdk = 24
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        vectorDrawables {
            useSupportLibrary = true
        }
    }

    signingConfigs{
        getByName("debug") {
            keyAlias = keystoreProperties["DEBUG_KEY_ALIAS"].toString()
            keyPassword = keystoreProperties["DEBUG_KEY_PASSWORD"].toString()
            storeFile = file(keystoreProperties["DEBUG_STORE_FILE"].toString())
            storePassword = keystoreProperties["DEBUG_STORE_PASSWORD"].toString()
        }
        create("release") {
            keyAlias = keystoreProperties["RELEASE_KEY_ALIAS"].toString()
            keyPassword = keystoreProperties["RELEASE_KEY_PASSWORD"].toString()
            storeFile = file(keystoreProperties["RELEASE_STORE_FILE"].toString())
            storePassword = keystoreProperties["RELEASE_STORE_PASSWORD"].toString()
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = true
            isShrinkResources = true
            signingConfig = signingConfigs.getByName("release")
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
        debug {
            isMinifyEnabled = false
            isShrinkResources = false
            applicationIdSuffix = ".debug"
            signingConfig = signingConfigs.getByName("debug")
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
        create("preprod"){
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }

    flavorDimensions.add("type")

    productFlavors {
        create("o2") {
            applicationIdSuffix = ".o2"
            dimension = "type"
        }
        create("vodafone") {
            applicationIdSuffix = ".vodafone"
            dimension = "type"
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
        kotlinCompilerExtensionVersion = "1.5.1"
    }
    packaging {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }
}

dependencies {

    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.lifecycle.runtime.ktx)
    implementation(libs.androidx.activity.compose)
    implementation(platform(libs.androidx.compose.bom))
    implementation(libs.androidx.ui)
    implementation(libs.androidx.ui.graphics)
    implementation(libs.androidx.ui.tooling.preview)
    implementation(libs.androidx.material3)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
    androidTestImplementation(platform(libs.androidx.compose.bom))
    androidTestImplementation(libs.androidx.ui.test.junit4)
    debugImplementation(libs.androidx.ui.tooling)
    debugImplementation(libs.androidx.ui.test.manifest)
}