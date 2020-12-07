#include "PreviewBeatmapPacket.hpp"

DEFINE_CLASS(MultiplayerExtensions::Beatmaps::PreviewBeatmapPacket);

namespace MultiplayerExtensions::Beatmaps {
	void PreviewBeatmapPacket::Serialize(LiteNetLib::Utils::NetDataWriter* writer) {
		writer->Put(levelId);
		writer->Put(levelKey);
		writer->Put(songName);
		writer->Put(songSubName);
		writer->Put(songAuthorName);
		writer->Put(levelAuthorName);
		writer->Put(beatsPerMinute);
		writer->Put(songDuration);

		writer->Put(isDownloadable);

		writer->Put(characteristic);
		writer->Put(difficulty);

		if (coverImage != nullptr) {
			writer->PutBytesWithLength(coverImage);
		}
		else {
			Array<uint8_t> emptyByteArray = Array<uint8_t>();
			writer->PutBytesWithLength(&emptyByteArray);
		}
	}

	void PreviewBeatmapPacket::Deserialize(LiteNetLib::Utils::NetDataReader* reader) {
		levelId = reader->GetString();
		levelKey = reader->GetString();
		songName = reader->GetString();
		songSubName = reader->GetString();
		songAuthorName = reader->GetString();
		levelAuthorName = reader->GetString();
		beatsPerMinute = reader->GetFloat();
		songDuration = reader->GetFloat();

		isDownloadable = reader->GetBool();

		characteristic = reader->GetString();
		difficulty = reader->GetUInt();

		coverImage = reader->GetBytesWithLength();
	}

	void PreviewBeatmapPacket::Release() {
		GlobalNamespace::ThreadStaticPacketPool_1<PreviewBeatmapPacket*>::get_pool()->Release(this);
	}
}