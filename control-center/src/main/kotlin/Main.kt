import androidx.compose.desktop.ui.tooling.preview.Preview
import androidx.compose.foundation.interaction.MutableInteractionSource
import androidx.compose.foundation.interaction.collectIsPressedAsState
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.material.Button
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.window.Window
import androidx.compose.ui.window.application
import kotlinx.coroutines.CoroutineScope

enum class Direction(val value: String) {
    F("F"),
    B("B"),
    L("L"),
    R("R")
}

enum class Velocity(val value: String) {
    B("B"),
    E("E")
}

val client = MqttHandler("mus-rover/in-controls")

@Composable
@Preview
fun App() {
    MaterialTheme {
        Column(modifier = Modifier.fillMaxWidth()) {
            Row(modifier = Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.Center) {
                DirectionalButton(Direction.F)
            }

            Row(modifier = Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.Center) {
                DirectionalButton(Direction.L)
                DirectionalButton(Direction.B)
                DirectionalButton(Direction.R)
            }
        }
    }
}

@Composable
fun DirectionalButton(direction: Direction) {
    val interactionSource = remember { MutableInteractionSource() }
    val pressed by interactionSource.collectIsPressedAsState()
    val coroutineScope = rememberCoroutineScope()

    if (pressed) {
        println(direction.value + Velocity.B.value)
        sendMessage(direction, Velocity.B, coroutineScope)

        DisposableEffect(Unit) {
            onDispose {
                println(direction.value + Velocity.E.value)
                sendMessage(direction, Velocity.E, coroutineScope)
            }
        }
    }

    Button(
        onClick = {},
        interactionSource = interactionSource,
    ) {
        Text(direction.value)
    }
}
fun sendMessage(direction: Direction, velocity: Velocity, coroutineScope: CoroutineScope) {
//    coroutineScope.launch(Dispatchers.IO) {
        client.publish(direction.value + velocity.value)
//    }
}

fun main() = application {
    Window(onCloseRequest = ::exitApplication) {
        App()
    }
}
