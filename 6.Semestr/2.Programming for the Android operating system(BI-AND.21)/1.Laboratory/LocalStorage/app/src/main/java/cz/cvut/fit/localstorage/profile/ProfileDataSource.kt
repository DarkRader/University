package cz.cvut.fit.localstorage.profile

import android.content.Context
import androidx.core.content.edit
import androidx.datastore.preferences.core.edit
import androidx.datastore.preferences.core.intPreferencesKey
import androidx.datastore.preferences.preferencesDataStore
import cz.cvut.fit.localstorage.appContext
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.distinctUntilChanged
import kotlinx.coroutines.flow.map

object ProfileDataSource {

    private val sharedPreferences = appContext.getSharedPreferences("fit_preferences", Context.MODE_PRIVATE)
    private val Context.dataStore by preferencesDataStore("fit_datastore")
    private val darkModeKey = intPreferencesKey("dark_mode")

    var name
        get() = sharedPreferences.getString("name", "").orEmpty()
        set(value) {
            sharedPreferences.edit {
                putString("name", value)
            }
        }

    suspend fun setDarkMode(mode: DarkMode) {
        appContext.dataStore.edit {
            it[darkModeKey] = mode.id
        }
    }

    fun getDarkModeStream(): Flow<DarkMode> {
        return appContext.dataStore.data.map {
            val darkModeId = it[darkModeKey]
            DarkMode.entries.find { it.id == darkModeId } ?: DarkMode.System
        }.distinctUntilChanged()
    }
}
