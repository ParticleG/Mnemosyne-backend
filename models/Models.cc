/**
 *
 *  Models.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Models.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::Mnemosyne;

const std::string Models::Cols::_id = "id";
const std::string Models::Cols::_format = "format";
const std::string Models::Cols::_name = "name";
const std::string Models::Cols::_tags = "tags";
const std::string Models::Cols::_keywords = "keywords";
const std::string Models::Cols::_data = "data";
const std::string Models::Cols::_uploader = "uploader";
const std::string Models::Cols::_collection = "collection";
const std::string Models::primaryKeyName = "";
const bool Models::hasPrimaryKey = false;
const std::string Models::tableName = "models";

const std::vector<typename Models::MetaData> Models::metaData_={
{"id","int32_t","integer",4,1,0,1},
{"format","std::string","text",0,0,0,0},
{"name","std::string","text",0,0,0,0},
{"tags","std::string","text",0,0,0,0},
{"keywords","std::string","text",0,0,0,0},
{"data","std::string","text",0,0,0,0},
{"uploader","int32_t","integer",4,0,0,0},
{"collection","int32_t","integer",4,0,0,0}
};
const std::string &Models::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Models::Models(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["format"].isNull())
        {
            format_=std::make_shared<std::string>(r["format"].as<std::string>());
        }
        if(!r["name"].isNull())
        {
            name_=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["tags"].isNull())
        {
            tags_=std::make_shared<std::string>(r["tags"].as<std::string>());
        }
        if(!r["keywords"].isNull())
        {
            keywords_=std::make_shared<std::string>(r["keywords"].as<std::string>());
        }
        if(!r["data"].isNull())
        {
            data_=std::make_shared<std::string>(r["data"].as<std::string>());
        }
        if(!r["uploader"].isNull())
        {
            uploader_=std::make_shared<int32_t>(r["uploader"].as<int32_t>());
        }
        if(!r["collection"].isNull())
        {
            collection_=std::make_shared<int32_t>(r["collection"].as<int32_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 8 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            format_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            name_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            tags_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            keywords_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            data_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            uploader_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            collection_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
    }

}

Models::Models(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 8)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            format_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            name_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            tags_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            keywords_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            data_=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
        }
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        dirtyFlag_[6] = true;
        if(!pJson[pMasqueradingVector[6]].isNull())
        {
            uploader_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[6]].asInt64());
        }
    }
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        dirtyFlag_[7] = true;
        if(!pJson[pMasqueradingVector[7]].isNull())
        {
            collection_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[7]].asInt64());
        }
    }
}

Models::Models(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("format"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["format"].isNull())
        {
            format_=std::make_shared<std::string>(pJson["format"].asString());
        }
    }
    if(pJson.isMember("name"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["name"].isNull())
        {
            name_=std::make_shared<std::string>(pJson["name"].asString());
        }
    }
    if(pJson.isMember("tags"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["tags"].isNull())
        {
            tags_=std::make_shared<std::string>(pJson["tags"].asString());
        }
    }
    if(pJson.isMember("keywords"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["keywords"].isNull())
        {
            keywords_=std::make_shared<std::string>(pJson["keywords"].asString());
        }
    }
    if(pJson.isMember("data"))
    {
        dirtyFlag_[5]=true;
        if(!pJson["data"].isNull())
        {
            data_=std::make_shared<std::string>(pJson["data"].asString());
        }
    }
    if(pJson.isMember("uploader"))
    {
        dirtyFlag_[6]=true;
        if(!pJson["uploader"].isNull())
        {
            uploader_=std::make_shared<int32_t>((int32_t)pJson["uploader"].asInt64());
        }
    }
    if(pJson.isMember("collection"))
    {
        dirtyFlag_[7]=true;
        if(!pJson["collection"].isNull())
        {
            collection_=std::make_shared<int32_t>((int32_t)pJson["collection"].asInt64());
        }
    }
}

void Models::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 8)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            format_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            name_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            tags_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            keywords_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            data_=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
        }
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        dirtyFlag_[6] = true;
        if(!pJson[pMasqueradingVector[6]].isNull())
        {
            uploader_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[6]].asInt64());
        }
    }
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        dirtyFlag_[7] = true;
        if(!pJson[pMasqueradingVector[7]].isNull())
        {
            collection_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[7]].asInt64());
        }
    }
}

void Models::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("format"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["format"].isNull())
        {
            format_=std::make_shared<std::string>(pJson["format"].asString());
        }
    }
    if(pJson.isMember("name"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["name"].isNull())
        {
            name_=std::make_shared<std::string>(pJson["name"].asString());
        }
    }
    if(pJson.isMember("tags"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["tags"].isNull())
        {
            tags_=std::make_shared<std::string>(pJson["tags"].asString());
        }
    }
    if(pJson.isMember("keywords"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["keywords"].isNull())
        {
            keywords_=std::make_shared<std::string>(pJson["keywords"].asString());
        }
    }
    if(pJson.isMember("data"))
    {
        dirtyFlag_[5] = true;
        if(!pJson["data"].isNull())
        {
            data_=std::make_shared<std::string>(pJson["data"].asString());
        }
    }
    if(pJson.isMember("uploader"))
    {
        dirtyFlag_[6] = true;
        if(!pJson["uploader"].isNull())
        {
            uploader_=std::make_shared<int32_t>((int32_t)pJson["uploader"].asInt64());
        }
    }
    if(pJson.isMember("collection"))
    {
        dirtyFlag_[7] = true;
        if(!pJson["collection"].isNull())
        {
            collection_=std::make_shared<int32_t>((int32_t)pJson["collection"].asInt64());
        }
    }
}

const int32_t &Models::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Models::getId() const noexcept
{
    return id_;
}
void Models::setId(const int32_t &pId) noexcept
{
    id_ = std::make_shared<int32_t>(pId);
    dirtyFlag_[0] = true;
}

const std::string &Models::getValueOfFormat() const noexcept
{
    const static std::string defaultValue = std::string();
    if(format_)
        return *format_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Models::getFormat() const noexcept
{
    return format_;
}
void Models::setFormat(const std::string &pFormat) noexcept
{
    format_ = std::make_shared<std::string>(pFormat);
    dirtyFlag_[1] = true;
}
void Models::setFormat(std::string &&pFormat) noexcept
{
    format_ = std::make_shared<std::string>(std::move(pFormat));
    dirtyFlag_[1] = true;
}
void Models::setFormatToNull() noexcept
{
    format_.reset();
    dirtyFlag_[1] = true;
}

const std::string &Models::getValueOfName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(name_)
        return *name_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Models::getName() const noexcept
{
    return name_;
}
void Models::setName(const std::string &pName) noexcept
{
    name_ = std::make_shared<std::string>(pName);
    dirtyFlag_[2] = true;
}
void Models::setName(std::string &&pName) noexcept
{
    name_ = std::make_shared<std::string>(std::move(pName));
    dirtyFlag_[2] = true;
}
void Models::setNameToNull() noexcept
{
    name_.reset();
    dirtyFlag_[2] = true;
}

const std::string &Models::getValueOfTags() const noexcept
{
    const static std::string defaultValue = std::string();
    if(tags_)
        return *tags_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Models::getTags() const noexcept
{
    return tags_;
}
void Models::setTags(const std::string &pTags) noexcept
{
    tags_ = std::make_shared<std::string>(pTags);
    dirtyFlag_[3] = true;
}
void Models::setTags(std::string &&pTags) noexcept
{
    tags_ = std::make_shared<std::string>(std::move(pTags));
    dirtyFlag_[3] = true;
}
void Models::setTagsToNull() noexcept
{
    tags_.reset();
    dirtyFlag_[3] = true;
}

const std::string &Models::getValueOfKeywords() const noexcept
{
    const static std::string defaultValue = std::string();
    if(keywords_)
        return *keywords_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Models::getKeywords() const noexcept
{
    return keywords_;
}
void Models::setKeywords(const std::string &pKeywords) noexcept
{
    keywords_ = std::make_shared<std::string>(pKeywords);
    dirtyFlag_[4] = true;
}
void Models::setKeywords(std::string &&pKeywords) noexcept
{
    keywords_ = std::make_shared<std::string>(std::move(pKeywords));
    dirtyFlag_[4] = true;
}
void Models::setKeywordsToNull() noexcept
{
    keywords_.reset();
    dirtyFlag_[4] = true;
}

const std::string &Models::getValueOfData() const noexcept
{
    const static std::string defaultValue = std::string();
    if(data_)
        return *data_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Models::getData() const noexcept
{
    return data_;
}
void Models::setData(const std::string &pData) noexcept
{
    data_ = std::make_shared<std::string>(pData);
    dirtyFlag_[5] = true;
}
void Models::setData(std::string &&pData) noexcept
{
    data_ = std::make_shared<std::string>(std::move(pData));
    dirtyFlag_[5] = true;
}
void Models::setDataToNull() noexcept
{
    data_.reset();
    dirtyFlag_[5] = true;
}

const int32_t &Models::getValueOfUploader() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(uploader_)
        return *uploader_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Models::getUploader() const noexcept
{
    return uploader_;
}
void Models::setUploader(const int32_t &pUploader) noexcept
{
    uploader_ = std::make_shared<int32_t>(pUploader);
    dirtyFlag_[6] = true;
}
void Models::setUploaderToNull() noexcept
{
    uploader_.reset();
    dirtyFlag_[6] = true;
}

const int32_t &Models::getValueOfCollection() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(collection_)
        return *collection_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Models::getCollection() const noexcept
{
    return collection_;
}
void Models::setCollection(const int32_t &pCollection) noexcept
{
    collection_ = std::make_shared<int32_t>(pCollection);
    dirtyFlag_[7] = true;
}
void Models::setCollectionToNull() noexcept
{
    collection_.reset();
    dirtyFlag_[7] = true;
}

void Models::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Models::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "format",
        "name",
        "tags",
        "keywords",
        "data",
        "uploader",
        "collection"
    };
    return inCols;
}

void Models::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getFormat())
        {
            binder << getValueOfFormat();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getTags())
        {
            binder << getValueOfTags();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getKeywords())
        {
            binder << getValueOfKeywords();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getData())
        {
            binder << getValueOfData();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getUploader())
        {
            binder << getValueOfUploader();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getCollection())
        {
            binder << getValueOfCollection();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Models::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if(dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    if(dirtyFlag_[6])
    {
        ret.push_back(getColumnName(6));
    }
    if(dirtyFlag_[7])
    {
        ret.push_back(getColumnName(7));
    }
    return ret;
}

void Models::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getFormat())
        {
            binder << getValueOfFormat();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getTags())
        {
            binder << getValueOfTags();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getKeywords())
        {
            binder << getValueOfKeywords();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getData())
        {
            binder << getValueOfData();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getUploader())
        {
            binder << getValueOfUploader();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[7])
    {
        if(getCollection())
        {
            binder << getValueOfCollection();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Models::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getFormat())
    {
        ret["format"]=getValueOfFormat();
    }
    else
    {
        ret["format"]=Json::Value();
    }
    if(getName())
    {
        ret["name"]=getValueOfName();
    }
    else
    {
        ret["name"]=Json::Value();
    }
    if(getTags())
    {
        ret["tags"]=getValueOfTags();
    }
    else
    {
        ret["tags"]=Json::Value();
    }
    if(getKeywords())
    {
        ret["keywords"]=getValueOfKeywords();
    }
    else
    {
        ret["keywords"]=Json::Value();
    }
    if(getData())
    {
        ret["data"]=getValueOfData();
    }
    else
    {
        ret["data"]=Json::Value();
    }
    if(getUploader())
    {
        ret["uploader"]=getValueOfUploader();
    }
    else
    {
        ret["uploader"]=Json::Value();
    }
    if(getCollection())
    {
        ret["collection"]=getValueOfCollection();
    }
    else
    {
        ret["collection"]=Json::Value();
    }
    return ret;
}

Json::Value Models::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 8)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getFormat())
            {
                ret[pMasqueradingVector[1]]=getValueOfFormat();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getName())
            {
                ret[pMasqueradingVector[2]]=getValueOfName();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getTags())
            {
                ret[pMasqueradingVector[3]]=getValueOfTags();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getKeywords())
            {
                ret[pMasqueradingVector[4]]=getValueOfKeywords();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getData())
            {
                ret[pMasqueradingVector[5]]=getValueOfData();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[6].empty())
        {
            if(getUploader())
            {
                ret[pMasqueradingVector[6]]=getValueOfUploader();
            }
            else
            {
                ret[pMasqueradingVector[6]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[7].empty())
        {
            if(getCollection())
            {
                ret[pMasqueradingVector[7]]=getValueOfCollection();
            }
            else
            {
                ret[pMasqueradingVector[7]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getFormat())
    {
        ret["format"]=getValueOfFormat();
    }
    else
    {
        ret["format"]=Json::Value();
    }
    if(getName())
    {
        ret["name"]=getValueOfName();
    }
    else
    {
        ret["name"]=Json::Value();
    }
    if(getTags())
    {
        ret["tags"]=getValueOfTags();
    }
    else
    {
        ret["tags"]=Json::Value();
    }
    if(getKeywords())
    {
        ret["keywords"]=getValueOfKeywords();
    }
    else
    {
        ret["keywords"]=Json::Value();
    }
    if(getData())
    {
        ret["data"]=getValueOfData();
    }
    else
    {
        ret["data"]=Json::Value();
    }
    if(getUploader())
    {
        ret["uploader"]=getValueOfUploader();
    }
    else
    {
        ret["uploader"]=Json::Value();
    }
    if(getCollection())
    {
        ret["collection"]=getValueOfCollection();
    }
    else
    {
        ret["collection"]=Json::Value();
    }
    return ret;
}

bool Models::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("format"))
    {
        if(!validJsonOfField(1, "format", pJson["format"], err, true))
            return false;
    }
    if(pJson.isMember("name"))
    {
        if(!validJsonOfField(2, "name", pJson["name"], err, true))
            return false;
    }
    if(pJson.isMember("tags"))
    {
        if(!validJsonOfField(3, "tags", pJson["tags"], err, true))
            return false;
    }
    if(pJson.isMember("keywords"))
    {
        if(!validJsonOfField(4, "keywords", pJson["keywords"], err, true))
            return false;
    }
    if(pJson.isMember("data"))
    {
        if(!validJsonOfField(5, "data", pJson["data"], err, true))
            return false;
    }
    if(pJson.isMember("uploader"))
    {
        if(!validJsonOfField(6, "uploader", pJson["uploader"], err, true))
            return false;
    }
    if(pJson.isMember("collection"))
    {
        if(!validJsonOfField(7, "collection", pJson["collection"], err, true))
            return false;
    }
    return true;
}
bool Models::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                std::string &err)
{
    if(pMasqueradingVector.size() != 8)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[4].empty())
      {
          if(pJson.isMember(pMasqueradingVector[4]))
          {
              if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[5].empty())
      {
          if(pJson.isMember(pMasqueradingVector[5]))
          {
              if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[6].empty())
      {
          if(pJson.isMember(pMasqueradingVector[6]))
          {
              if(!validJsonOfField(6, pMasqueradingVector[6], pJson[pMasqueradingVector[6]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[7].empty())
      {
          if(pJson.isMember(pMasqueradingVector[7]))
          {
              if(!validJsonOfField(7, pMasqueradingVector[7], pJson[pMasqueradingVector[7]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Models::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    if(pJson.isMember("format"))
    {
        if(!validJsonOfField(1, "format", pJson["format"], err, false))
            return false;
    }
    if(pJson.isMember("name"))
    {
        if(!validJsonOfField(2, "name", pJson["name"], err, false))
            return false;
    }
    if(pJson.isMember("tags"))
    {
        if(!validJsonOfField(3, "tags", pJson["tags"], err, false))
            return false;
    }
    if(pJson.isMember("keywords"))
    {
        if(!validJsonOfField(4, "keywords", pJson["keywords"], err, false))
            return false;
    }
    if(pJson.isMember("data"))
    {
        if(!validJsonOfField(5, "data", pJson["data"], err, false))
            return false;
    }
    if(pJson.isMember("uploader"))
    {
        if(!validJsonOfField(6, "uploader", pJson["uploader"], err, false))
            return false;
    }
    if(pJson.isMember("collection"))
    {
        if(!validJsonOfField(7, "collection", pJson["collection"], err, false))
            return false;
    }
    return true;
}
bool Models::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                              const std::vector<std::string> &pMasqueradingVector,
                                              std::string &err)
{
    if(pMasqueradingVector.size() != 8)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
      if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
      {
          if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
              return false;
      }
      if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
      {
          if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, false))
              return false;
      }
      if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
      {
          if(!validJsonOfField(6, pMasqueradingVector[6], pJson[pMasqueradingVector[6]], err, false))
              return false;
      }
      if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
      {
          if(!validJsonOfField(7, pMasqueradingVector[7], pJson[pMasqueradingVector[7]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Models::validJsonOfField(size_t index,
                              const std::string &fieldName,
                              const Json::Value &pJson,
                              std::string &err,
                              bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            else
            {
                err="The automatic primary key cannot be update";
                return false;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 3:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 4:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 5:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 6:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 7:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
            break;
    }
    return true;
}