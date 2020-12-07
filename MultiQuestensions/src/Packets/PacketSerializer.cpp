#include "PacketSerializer.hpp"

DEFINE_CLASS(MultiQuestensions::PacketSerializer);

namespace MultiQuestensions {
	void PacketSerializer::Serialize(LiteNetLib::Utils::NetDataWriter* writer, LiteNetLib::Utils::INetSerializable* packet) {
		System::Type* packetType = il2cpp_utils::GetSystemType(il2cpp_functions::object_get_class(reinterpret_cast<Il2CppObject*>(packet)));
		
		writer->Put(packetType->ToString());
		packet->LiteNetLib_Utils_INetSerializable_Serialize(writer);
	}

	void PacketSerializer::Deserialize(LiteNetLib::Utils::NetDataReader* reader, int length, GlobalNamespace::IConnectedPlayer* data) {
		Il2CppString* packetType = reader->GetString();
		if (packetHandlers->ContainsKey(packetType)) {
			packetHandlers->get_Item(packetType)->Invoke(reader, length, data);
		}
	}

	bool PacketSerializer::HandlesType(System::Type* type) {
		return registeredTypes->Contains(type->ToString());
	}

	void PacketSerializer::RegisterCallback(Il2CppString* identifier, CallbackAction* callback) {
		registeredTypes->Add(identifier);
		packetHandlers->set_Item(identifier, callback);
	}
}