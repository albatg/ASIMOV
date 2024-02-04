#ifndef ASIMOV_LIBRARY_H
#define ASIMOV_LIBRARY_H
#include <QTextEdit>
#include<QString>


#endif // ASIMOV_LIBRARY_H

// --------------------------------------------------------
//                     TPathway
// --------------------------------------------------------
class TPathway
{
    private:

    public:
        // constructors

        // getters/setters

        //public methods

};
//=========================================================


// --------------------------------------------------------
//                       TRawInput
// --------------------------------------------------------
class TRawInput
{
    private:
        bool m_loaded;
        QString* m_source;

    public:
        // constructors
        TRawInput(QString* v_source = nullptr);
        ~TRawInput();

        // getters/setters
        QString getSource();
        void setSource(QString* v_source);
        bool getLoaded();

        //public methods
        bool loadFromFile();
        void setToFile();
        void Edit(QTextEdit* editor);
        void newRawInput();
        unsigned short verifyModel();
        bool createModel(TPathway& v_model);
        void clean();
};
//=========================================================


// --------------------------------------------------------
//                     TModelMetabolite
// --------------------------------------------------------
class TModelMetabolite
{
    private:
        QString m_name;
        QString m_id;
        double m_initValue;
        double m_topValue;
        double m_bottomValue;
        double m_value;
        double m_precision;
        bool m_tag;

    public:
        // constructor
        TModelMetabolite(QString m_name, QString m_id, double m_initValue, double m_topValue,
                         double m_bottomValue, double m_value, double m_precision, bool m_tag);

        // getters/setters
        QString getName();
        QString getId();
        double getInitValue();
        double getTopValue();
        double getBottomValue();
        double getValue();
        double getPrecision();
        bool getTag();

        void setValue(double v_value);
        void setTag(bool v_tag);

        // other methods
        double range();

};
//=========================================================


// --------------------------------------------------------
//                     TModelParameter
// --------------------------------------------------------
class TModelParameter
{
    private:
        short int m_index;
        QString m_id;
        QString m_description;
        double m_value;
        double m_precision;
        bool m_tag;

    public:
        // constructors
        TModelParameter(short int v_Index = -1, QString m_ID = "",
                        QString m_Description = "", double m_Value = 0,
                        double m_Precision = 0, bool m_Tag = false);

        // getters/setters
        short int getIndex();
        void setIndex(short int v_index);
        QString getId();
        void setid(QString v_id);
        QString getDescription();
        void setDescription(QString v_description);
        double getValue();
        void setValue(double v_value);
        double getPrecision();
        void setPrecision(double v_precision);
        bool getTag();
        void setTag(bool v_tag);


        //public methods

};
//=========================================================


// --------------------------------------------------------
//                    TModelReaction
// --------------------------------------------------------
class TModelReaction
{
    private:
        short int m_index;
        QString m_id;
        QString m_description;
        std::vector<int> m_reagent;
        std::vector<int> m_product;
        std::vector<int> m_parameter;
        QString m_equation;
        bool m_tag;

    public:
        // constructors
        TModelReaction(short int v_Index = -1, QString v_ID = "",
                       QString v_Description = "", std::vector<int> v_Reagent= { 0 },
                       std::vector<int> v_Product = { 0 },
                       std::vector<int> v_Parameter= { 0 }, QString v_Equation= "",
                       bool v_Tag = false);

        // getters/setters
        short int getIndex();
        void setIndex(short int v_index);
        QString getId();
        void setid(QString v_id);
        QString getDescription();
        void setDescription(QString v_description);
        std::vector<int> getAllReagents();
        void setAllReagents(std::vector<int> v_reagents);
        std::vector<int> getAllProducts();
        void setAllProducts(std::vector<int> v_products);
        std::vector<int> getAllParameters();
        void setAllParameters(std::vector<int> v_parameters);
        int GetReagentNo ();
        void SetReagentNo(std::vector<int>(int i));
        int GetProductNo ();
        void SetProductNo(std::vector<int>(int i));
        int GetOarameterNo ();
        void SetParameterNo(std::vector<int>(int i));
        QString getEquation();
        void setEquation(QString v_equation);
        bool getTag();
        void setTag(bool v_tag);

        //public methods
        int ReagentsCount();
        int ProductsCount();
        int ParametersCount();
        TModelMetabolite &Reagent(const int index);
        TModelMetabolite &Product(const int index);
        TModelMetabolite &Parameter(const int index);

};
//=========================================================


// --------------------------------------------------------
//                     TRunConfig
// --------------------------------------------------------
class TRunConfig
{
    private:
        double m_initTime;
        double m_endTime;
        size_t m_cycles;
        QString m_paramList;


    public:
        // constructors
        TRunConfig(double v_initTime = 0, double v_endTime    = 0,
                   size_t v_cycles   = 0, QString v_paramList = ""):
                   m_initTime(v_initTime), m_endTime (v_endTime),
                   m_cycles (v_cycles), m_paramList (v_paramList){};

        // getters/setters
        double getInitTime();
        void setInitTime(double t);
        double getEndTime();
        void setEndTime(double t);
        size_t getCycles();
        void setCycles(size_t value);
        QString getParamList();
        void setParamList(QString pList);


        //public methods

};
//=========================================================


// --------------------------------------------------------
//                     TFrameData
// --------------------------------------------------------
class TFrameData
{
    private:

    public:
        // constructors

        // getters/setters

        //public methods

};
//=========================================================





