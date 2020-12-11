#ifndef COUNTRYLISTMODEL_H
#define COUNTRYLISTMODEL_H

#include <QAbstractListModel>

class Country : public QObject {
    Q_OBJECT

    Q_PROPERTY(qint16 numericCode READ numericCode CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString alpha2Code READ alpha2Code CONSTANT)
    Q_PROPERTY(QString alpha3Code READ alpha3Code CONSTANT)
    Q_PROPERTY(QString region READ region CONSTANT)

public:
    explicit Country(qint16 numericCode, const QString& name, const QString& alpha2Code,
        const QString& alpha3Code, QString region, QObject* parent = nullptr)
        : QObject(parent)
        , m_numericCode(numericCode)
        , m_name(name)
        , m_alpha2Code(alpha2Code)
        , m_alpha3Code(alpha3Code)
        , m_region(region)
    {
    }

    qint16 numericCode() const { return m_numericCode; }
    QString name() const { return m_name; }
    QString alpha2Code() const { return m_alpha2Code; }
    QString alpha3Code() const { return m_alpha3Code; }
    QString region() const { return m_region; }

private:
    // TODO (camar) : Add native name
    qint16 m_numericCode = -1;
    QString m_name = "";
    QString m_alpha2Code = "";
    QString m_alpha3Code = "";
    QString m_region = "";
};

class CountryListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum CountryRoles {
        NumericCodeRole = Qt::UserRole + 1,
        NameRole,
        Alpha2CodeRole,
        Alpha3CodeRole,
        RegionRole
    };
    Q_ENUM(CountryRoles)

    explicit CountryListModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // NOTE (camar) : override for QML. Without it, QML sees only the 2-parameters and 3-parameters
    // versions.
    Q_INVOKABLE QModelIndex index(
        int row, int column = 0, const QModelIndex& parent = QModelIndex()) const override;

    void append(const Country* location);

private:
    QList<const Country*> m_countries;
};

#endif // COUNTRYLISTMODEL_H
