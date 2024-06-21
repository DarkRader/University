package cz.cvut.fit.kuznear1.firebase.features.profile.presentation

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.google.firebase.analytics.FirebaseAnalytics
import com.google.firebase.crashlytics.FirebaseCrashlytics
import cz.cvut.fit.kuznear1.firebase.features.profile.data.UserRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class ProfileViewModel(
    private val userRepository: UserRepository,
    private val firebaseCrashlytics: FirebaseCrashlytics,
    private val firebaseAnalytics: FirebaseAnalytics,
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(ProfileScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            userRepository.userState.collect { user ->
                firebaseAnalytics.setUserId(user?.id)
                _screenStateStream.update {
                    it.copy(id = user?.id, name = user?.name)
                }
            }
        }
    }

    fun logOut() {
        firebaseCrashlytics.recordException(IllegalStateException("Non fatal exception during log out"))
        userRepository.logOut()
    }
}

data class ProfileScreenState(
    val id: String? = null,
    val name: String? = null,
)
