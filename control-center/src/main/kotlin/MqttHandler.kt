import mqtt.MQTTVersion
import mqtt.packets.Qos
import mqtt.packets.mqttv5.ReasonCode

@OptIn(ExperimentalUnsignedTypes::class)
class MqttHandler(
    private val topic: String
) {
    private var client: MQTTClient = MQTTClient(
        MQTTVersion.MQTT5,
        "broker.mqttdashboard.com",
        1883,
        null,
        clientId = "control-center"
    ) { message ->
        println(message.payload?.toByteArray()?.decodeToString())
    }

//    init {
//        client.publish(false, Qos.AT_MOST_ONCE, topic, "WB".encodeToByteArray().toUByteArray())
//        client.run()
//    }

    fun disconnect() {
        println("Disconnecting from MQTT broker")
        client.disconnect(ReasonCode.SUCCESS)
    }

    fun publish(message: String) {
        println("Publishing message to topic $topic: $message")
        client.publish(false, Qos.AT_MOST_ONCE, topic, message.encodeToByteArray().toUByteArray())
        client.step()
        println("Finish publish")
    }

    fun subscribe() {}

    fun unsubscribe() {}
}