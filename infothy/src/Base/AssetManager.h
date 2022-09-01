#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <functional>
#include "raylib/raylib.h"

template <typename AssetType>
class AssetManager {
private:
	using _typeUnloaderCb = std::function<void(AssetType)>;

	static AssetManager* _instance;
	std::unordered_map<const char*, std::shared_ptr<AssetType>> _assets;

	// Unloader callback function
	_typeUnloaderCb _unloader_cb;

	void unloadAsset(const std::shared_ptr<AssetType>& asset) {
		if (asset == nullptr || !_unloader_cb)
			return;
		_unloader_cb(*asset);
	}

	AssetManager() : _assets{}, _unloader_cb{} {}

	AssetManager(_typeUnloaderCb cb) : _assets{}, _unloader_cb { cb } {}

	~AssetManager() {
		for (auto& it : _assets)
			unloadAsset(it.second);

		delete _instance;
	}

public:

	static AssetManager* getInstance() {
		if (_instance == nullptr) {
			_instance = new AssetManager();
		}
		return _instance;
	}

	static AssetManager* getInstance(_typeUnloaderCb cb) {
		if (_instance == nullptr) {
			_instance = new AssetManager(cb);
		}
		return _instance;
	}

	void release() {
		_instance = nullptr;
	}

	void load(const char* assetId, AssetType&& asset) {
		if (_assets.contains(assetId))
			return;

		_assets.emplace(std::make_pair(assetId, std::make_shared<AssetType>(std::move(asset))));
	}

	void unload(const char* assetId) {
		if (!_assets.contains(assetId))
			return;

		unloadAsset(_assets.at(assetId));
		_assets.erase(assetId);
	}

	std::shared_ptr<AssetType> get(const char* assetId) {
		if (!_assets.contains(assetId))
			return nullptr;

		return _assets.at(assetId);
	}

};

template <typename AssetType>
AssetManager<AssetType>* AssetManager<AssetType>::_instance = nullptr;