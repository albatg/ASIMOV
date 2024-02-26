/**
 *@file asimov_library.h
 *@version 1.0
 *@date 22/02/2024
 *@author Grupo ASIMOV
 *@title Librería para proyecto interdisciplinar de modelización del proceso de la glucólisis en una célula
*
*/
#ifndef ASIMOV_LIBRARY_H
#define ASIMOV_LIBRARY_H
#include <QTextEdit>
#include<QString>


#endif // ASIMOV_LIBRARY_H

class TPathway;


/**
 *@brief Definición de la clase TRawInput que implementa un tipo de dato para poder gestionar los archivos de entrada
 *       del programa.
*/
class TRawInput
{
    private:    // private members
        /**
         * @brief Variable booleana que indica si se ha cargado un archivo
        */
        bool m_loaded;
        /**
         * @brief Variable de tipo QString en el que se guardará el contenido del archivo
        */
        QString* m_source;

    public:
        /**
         * @brief Constructor por defecto de la clase
         * @param v_source Apunta a nullptr por defecto.
         * @post Genera una instancia de la clase TRawInput con su contenido vacío.
        */
        TRawInput(QString* v_source = nullptr);

        /**
         * @brief Destructor de instancias de tipo TRawInput
         *
        */
        ~TRawInput();

        //getters/setters
        /**
         * @brief Método que devuelve el contenido de una fuente
         * @return Devuelve un QString que se corresponde con el valor de la fuente.
        */
        QString getSource();

        /**
         * @brief Método que establece el valor de la fuente.
         * @param v_source Puntero a un objeto QString que se asignará como fuente.
         * @post El objeto m_source queda apuntando al objeto QString proporcionado.
        */
        void setSource(QString* v_source);

        /**
         * @brief Método que devuelve si se ha cargado una fuente(archivo) o no.
         * @return Devuelve true en función de si m_source tiene contenido, en caso contrario devuelve false.
        */
        bool getLoaded();

        //public methods
        /**
         * @brief Intenta cargar contenido desde un archivo a m_source.
         * @details Este método verifica que m_source esté configurada y no esté vacía.
         *          Luego intenta abrir el archivo indicado por m_source en modo de solo lectura.
         *          Si la apertura del archivo es exitosa, lee su contenido y lo almacena en m_source.
         *          Finalmente, marca m_loaded como verdadero y muestra un mensaje de éxito en la consola.
         * @return Devuelve true si la carga desde el archivo fue exitosa, false en caso contrario.
        */
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


// --------------------------------------------------------
//                     TModelParameter
// --------------------------------------------------------

/**
 *@brief Esta clase encapsula información sobre un parámetro y se usa para representar y manipular parámetros específicos
 *      relacionados con la glucólisis.
*/
class TModelParameter
{
    private:    // private members
        /**
         *@brief Contador estático utilizado internamente para el índice.
        */
        static short int s_counter;
        /**
         *@brief Índice del parámetro.
        */
        short int m_index;
        /**
         *@brief Identificación única para el parámetro.
        */
        QString m_id;
        /**
         *@brief Decripción del parámetro.
        */
        QString m_description;
        /**
         *@brief Valor numértico del parámetro.
        */
        double m_value;
        /**
         *@brief Precición asociada al valor del parámetro.
        */
        double m_precision;
        /**
         *@brief Etiqueta para marcar en caso de que queramos hacer un uso específico de ese parámetro.
        */
        bool m_tag;

    public:
        // constructor por defecto
       /* TModelParameter(/*short int v_Index = -1 QString m_ID = "",
                        QString m_Description = "", double m_Value = 0,
                        double m_Precision = 0, bool m_Tag = false);*/

        TModelParameter(QString m_ID, QString m_Description, double m_Value,double m_Precision, bool m_Tag);

        short int getIndex();
        //void setIndex(short int v_index);
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
};



// --------------------------------------------------------
//                    TModelReaction
// --------------------------------------------------------


class TModelReaction
{
    private:    // private members
        short int m_index;
        QString m_id;
        QString m_description;
        std::vector<int> m_reagent;
        std::vector<int> m_product;
        std::vector<int> m_parameter;
        QString m_equation;
        bool m_tag;

    public:     // constructors
        TModelReaction(short int v_Index = -1, QString v_ID = "",
                       QString v_Description = "", std::vector<int> v_Reagent= { 0 },
                       std::vector<int> v_Product = { 0 },
                       std::vector<int> v_Parameter= { 0 }, QString v_Equation= "",
                       bool v_Tag = false);

    public:     // getters/setters
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

    public:     //public methods
        int ReagentsCount();
        int ProductsCount();
        int ParametersCount();
        TModelMetabolite &Reagent(const int index);
        TModelMetabolite &Product(const int index);
        TModelMetabolite &Parameter(const int index);

};


// --------------------------------------------------------
//                     TRunConfig
// --------------------------------------------------------


class TRunConfig
{
    private:    // private members
        double m_initTime;
        double m_endTime;
        size_t m_cycles;
        QString m_paramList;


    public:     // constructors
        TRunConfig(double v_initTime = 0, double v_endTime    = 0,
                   size_t v_cycles   = 0, QString v_paramList = ""):
                   m_initTime(v_initTime), m_endTime (v_endTime),
                   m_cycles (v_cycles), m_paramList (v_paramList){};

    public:     // getters/setters
        double getInitTime();
        void setInitTime(double t);
        double getEndTime();
        void setEndTime(double t);
        size_t getCycles();
        void setCycles(size_t value);
        QString getParamList();
        void setParamList(QString pList);


    public:     //public methods

};


// --------------------------------------------------------
//                     TFrameData
// --------------------------------------------------------


class TFrameData
{
private:    // private members

public:     // constructors

public:     // getters/setters

public:     //public methods

};


// --------------------------------------------------------
//                     TPathway
// --------------------------------------------------------


class TPathway
{
private:    // private members

public:     // constructors

public:     // getters/setters

public:     //public methods

};


