using Microsoft.VisualStudio.Text.Classification;
using Microsoft.VisualStudio.Utilities;
using System.ComponentModel.Composition;
using System.Windows.Media;

namespace NinginToolsExtension
{
    /// <summary>
    /// Defines an editor format for the NinginScene type that has a purple background
    /// and is underlined.
    /// </summary>
    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginScene")]
    [Name("NinginScene")]
    [UserVisible(true)] // This should be visible to the end user
    [Order(Before = Priority.Default)] // Set the priority to be after the default classifiers
    internal sealed class NinginSceneFormat : ClassificationFormatDefinition
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="NinginSceneFormat"/> class.
        /// </summary>
        public NinginSceneFormat()
        {
            this.DisplayName = "NinginScene"; // Human readable version of the name
        }
    }

    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginSceneIdentifier")]
    [Name("NinginSceneIdentifier")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneIdentifierFormat : ClassificationFormatDefinition
    {
        public NinginSceneIdentifierFormat()
        {
            this.DisplayName = "Ningin Scene Identifier";
            this.ForegroundColor = Colors.Wheat;
        }
    }

    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginSceneHeadIdentifier")]
    [Name("NinginSceneHeadIdentifier")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneHeadIdentifierFormat : ClassificationFormatDefinition
    {
        public NinginSceneHeadIdentifierFormat()
        {
            this.DisplayName = "Ningin Scene Head Identifier";
            this.ForegroundColor = Color.FromRgb(79, 193, 255);
        }
    }

    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginSceneChildIdentifier")]
    [Name("NinginSceneChildIdentifier")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneChildIdentifierFormat : ClassificationFormatDefinition
    {
        public NinginSceneChildIdentifierFormat()
        {
            this.DisplayName = "Ningin Scene Child Identifier";
            this.ForegroundColor = Colors.SpringGreen;
        }
    }
    
    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginSceneTypeIdentifier")]
    [Name("NinginSceneTypeIdentifier")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneTypeIdentifierFormat : ClassificationFormatDefinition
    {
        public NinginSceneTypeIdentifierFormat()
        {
            this.DisplayName = "Ningin Scene Type Identifier";
            this.ForegroundColor = Color.FromRgb(86, 156, 214);
        }
    }

    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginSceneString")]
    [Name("NinginSceneString")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneStringFormat : ClassificationFormatDefinition
    {
        public NinginSceneStringFormat()
        {
            this.DisplayName = "Ningin Scene String";
            this.ForegroundColor = Color.FromRgb(214, 157, 133);
        }
    }

    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginSceneBool")]
    [Name("NinginSceneBool")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneBoolFormat : ClassificationFormatDefinition
    {
        public NinginSceneBoolFormat()
        {
            this.DisplayName = "Ningin Scene Bool";
            this.ForegroundColor = Color.FromRgb(86, 156, 214);
        }
    }

    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginSceneNumber")]
    [Name("NinginSceneNumber")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneNumberFormat : ClassificationFormatDefinition
    {
        public NinginSceneNumberFormat()
        {
            this.DisplayName = "Ningin Scene Number";
            this.ForegroundColor = Colors.LightGreen;
        }
    }

    [Export(typeof(EditorFormatDefinition))]
    [ClassificationType(ClassificationTypeNames = "NinginSceneComment")]
    [Name("NinginSceneComment")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneStringLiteralFormat : ClassificationFormatDefinition
    {
        public NinginSceneStringLiteralFormat()
        {
            this.DisplayName = "Ningin Scene Comment";
            this.ForegroundColor = Colors.Green; // Set the color for string literals
        }
    }
}
