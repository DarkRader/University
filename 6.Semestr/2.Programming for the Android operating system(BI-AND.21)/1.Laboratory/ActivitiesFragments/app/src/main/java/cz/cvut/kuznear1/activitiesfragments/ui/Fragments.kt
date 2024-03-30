package cz.cvut.kuznear1.activitiesfragments.ui

import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.ComposeView
import androidx.compose.ui.platform.ViewCompositionStrategy
import androidx.compose.ui.unit.dp
import androidx.fragment.app.Fragment

class MainFragment : Fragment() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.d(this::class.simpleName, "onCreate")
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return ComposeView(requireContext()).apply {
            setViewCompositionStrategy(ViewCompositionStrategy.DisposeOnViewTreeLifecycleDestroyed)
            setContent { MainFragmentScreen() }
        }
    }

    override fun onStart() {
        super.onStart()
        Log.d(this::class.simpleName, "onStart")
    }

    override fun onResume() {
        super.onResume()
        Log.d(this::class.simpleName, "onResume")
    }

    override fun onPause() {
        super.onPause()
        Log.d(this::class.simpleName, "onPause")
    }

    override fun onStop() {
        super.onStop()
        Log.d(this::class.simpleName, "onStop")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d(this::class.simpleName, "onDestroy")
    }
}

@Composable
private fun MainFragmentScreen() {
    Text(
        text = "Main fragment",
        modifier = Modifier
            .fillMaxSize()
            .background(color = Color.Magenta)
            .padding(16.dp),
    )
}
