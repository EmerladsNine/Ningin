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
    [ClassificationType(ClassificationTypeNames = "NinginSceneKeyword")]
    [Name("NinginSceneKeyword")]
    [UserVisible(true)]
    [Order(Before = Priority.Default)]
    internal sealed class NinginSceneKeywordFormat : ClassificationFormatDefinition
    {
        public NinginSceneKeywordFormat()
        {
            this.DisplayName = "Ningin Scene Keyword";
            this.ForegroundColor = Colors.Blue; // Set the color for keywords
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
