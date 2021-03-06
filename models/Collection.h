/**
 *
 *  Collection.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace Mnemosyne
{

class Collection
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _name;
        static const std::string _description;
        static const std::string _tags;
        static const std::string _content;
        static const std::string _extra;
        static const std::string _preview;
        static const std::string _creator;
        static const std::string _created;
        static const std::string _visibility;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    using PrimaryKeyType = int64_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Collection(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Collection(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Collection(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Collection() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int64_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getId() const noexcept;
    ///Set the value of the column id
    void setId(const int64_t &pId) noexcept;

    /**  For column name  */
    ///Get the value of the column name, returns the default value if the column is null
    const std::string &getValueOfName() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getName() const noexcept;
    ///Set the value of the column name
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column description  */
    ///Get the value of the column description, returns the default value if the column is null
    const std::string &getValueOfDescription() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    ///Set the value of the column description
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;
    void setDescriptionToNull() noexcept;

    /**  For column tags  */
    ///Get the value of the column tags, returns the default value if the column is null
    const std::string &getValueOfTags() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getTags() const noexcept;
    ///Set the value of the column tags
    void setTags(const std::string &pTags) noexcept;
    void setTags(std::string &&pTags) noexcept;

    /**  For column content  */
    ///Get the value of the column content, returns the default value if the column is null
    const std::string &getValueOfContent() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getContent() const noexcept;
    ///Set the value of the column content
    void setContent(const std::string &pContent) noexcept;
    void setContent(std::string &&pContent) noexcept;

    /**  For column extra  */
    ///Get the value of the column extra, returns the default value if the column is null
    const std::string &getValueOfExtra() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getExtra() const noexcept;
    ///Set the value of the column extra
    void setExtra(const std::string &pExtra) noexcept;
    void setExtra(std::string &&pExtra) noexcept;
    void setExtraToNull() noexcept;

    /**  For column preview  */
    ///Get the value of the column preview, returns the default value if the column is null
    const std::string &getValueOfPreview() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getPreview() const noexcept;
    ///Set the value of the column preview
    void setPreview(const std::string &pPreview) noexcept;
    void setPreview(std::string &&pPreview) noexcept;
    void setPreviewToNull() noexcept;

    /**  For column creator  */
    ///Get the value of the column creator, returns the default value if the column is null
    const int64_t &getValueOfCreator() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getCreator() const noexcept;
    ///Set the value of the column creator
    void setCreator(const int64_t &pCreator) noexcept;

    /**  For column created  */
    ///Get the value of the column created, returns the default value if the column is null
    const ::trantor::Date &getValueOfCreated() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getCreated() const noexcept;
    ///Set the value of the column created
    void setCreated(const ::trantor::Date &pCreated) noexcept;

    /**  For column visibility  */
    ///Get the value of the column visibility, returns the default value if the column is null
    const std::string &getValueOfVisibility() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getVisibility() const noexcept;
    ///Set the value of the column visibility
    void setVisibility(const std::string &pVisibility) noexcept;
    void setVisibility(std::string &&pVisibility) noexcept;


    static size_t getColumnNumber() noexcept {  return 10;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<Collection>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Collection>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int64_t> id_;
    std::shared_ptr<std::string> name_;
    std::shared_ptr<std::string> description_;
    std::shared_ptr<std::string> tags_;
    std::shared_ptr<std::string> content_;
    std::shared_ptr<std::string> extra_;
    std::shared_ptr<std::string> preview_;
    std::shared_ptr<int64_t> creator_;
    std::shared_ptr<::trantor::Date> created_;
    std::shared_ptr<std::string> visibility_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[10]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "id,";
            ++parametersCount;
        sql += "name,";
        ++parametersCount;
        if(!dirtyFlag_[1])
        {
            needSelection=true;
        }
        if(dirtyFlag_[2])
        {
            sql += "description,";
            ++parametersCount;
        }
        sql += "tags,";
        ++parametersCount;
        if(!dirtyFlag_[3])
        {
            needSelection=true;
        }
        sql += "content,";
        ++parametersCount;
        if(!dirtyFlag_[4])
        {
            needSelection=true;
        }
        if(dirtyFlag_[5])
        {
            sql += "extra,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "preview,";
            ++parametersCount;
        }
        sql += "creator,";
        ++parametersCount;
        if(!dirtyFlag_[7])
        {
            needSelection=true;
        }
        sql += "created,";
        ++parametersCount;
        if(!dirtyFlag_[8])
        {
            needSelection=true;
        }
        sql += "visibility,";
        ++parametersCount;
        if(!dirtyFlag_[9])
        {
            needSelection=true;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        sql +="default,";
        if(dirtyFlag_[1])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[2])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[3])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[4])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[5])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[6])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[7])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[8])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[9])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace Mnemosyne
} // namespace drogon_model
